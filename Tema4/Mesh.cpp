#include "Mesh.h"


////////////////////////////////////////////////////////////
// OFF FILE READING CODE
////////////////////////////////////////////////////////////

//Mesh *
int Mesh::ReadOffFile(const char *filename)
{
	// Open file
	FILE *fp;
	if (!(fp = fopen(filename, "r"))) {
		fprintf(stderr, "Unable to open file %s\n", filename);
		return -1;
	}

	// Read file
	int nverts = 0;
	int nfaces = 0;
	int nedges = 0;
	int line_count = 0;
	char buffer[1024];
	while (fgets(buffer, 1023, fp)) {
		// Increment line counter
		line_count++;

		// Skip white space
		char *bufferp = buffer;
		while (isspace(*bufferp)) bufferp++;

		// Skip blank lines and comments
		if (*bufferp == '#') continue;
		if (*bufferp == '\0') continue;

		// Check section
		if (nverts == 0) {
			// Read header 
			if (!strstr(bufferp, "OFF")) {
				// Read mesh counts
				if ((sscanf(bufferp, "%d%d%d", &nverts, &nfaces, &nedges) != 3) || (nverts == 0)) {
					fprintf(stderr, "Syntax error reading header on line %d in file %s\n", line_count, filename);
					fclose(fp);
					return -1;
				}

				// Allocate memory for mesh
				this->verts = new Vertex [nverts];
				assert(this->verts);
				this->faces = new Face [nfaces];
				assert(this->faces);
			}
		}
		else if (this->nverts < nverts) {
			// Read vertex coordinates
			Vertex& vert = this->verts[this->nverts++];
			if (sscanf(bufferp, "%f%f%f", &(vert.x), &(vert.y), &(vert.z)) != 3) {
				fprintf(stderr, "Syntax error with vertex coordinates on line %d in file %s\n", line_count, filename);
				fclose(fp);
				return -1;
			}
		}
		else if (this->nfaces < nfaces) {
			// Get next face
			Face& face = this->faces[this->nfaces++];

			// Read number of vertices in face 
			bufferp = strtok(bufferp, " \t");
			if (bufferp) face.nverts = atoi(bufferp);
			else {
				fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
				fclose(fp);
				return -1;
			}

			// Allocate memory for face vertices
			face.verts = new Vertex *[face.nverts];
			assert(face.verts);

			// Read vertex indices for face
			for (int i = 0; i < face.nverts; i++) {
				bufferp = strtok(NULL, " \t");
				if (bufferp) face.verts[i] = &(this->verts[atoi(bufferp)]);
				else {
					fprintf(stderr, "Syntax error with face on line %d in file %s\n", line_count, filename);
					fclose(fp);
					return -1;
				}
			}

			// Compute normal for face
			face.normal[0] = face.normal[1] = face.normal[2] = 0;
			Vertex *v1 = face.verts[face.nverts-1];
			for (int i = 0; i < face.nverts; i++) {
				Vertex *v2 = face.verts[i];
				face.normal[0] += (v1->y - v2->y) * (v1->z + v2->z);
				face.normal[1] += (v1->z - v2->z) * (v1->x + v2->x);
				face.normal[2] += (v1->x - v2->x) * (v1->y + v2->y);
				v1 = v2;
			}

			// Normalize normal
			float squared_normal_length = 0.0;
			squared_normal_length += face.normal[0]*face.normal[0];
			squared_normal_length += face.normal[1]*face.normal[1];
			squared_normal_length += face.normal[2]*face.normal[2];
			float normal_length = sqrt(squared_normal_length);
			if (normal_length > 1.0E-6) {
				face.normal[0] /= normal_length;
				face.normal[1] /= normal_length;
				face.normal[2] /= normal_length;
			}
		}
		else {
			// Should never get here
			fprintf(stderr, "Found extra text starting at line %d in file %s\n", line_count, filename);
			break;
		}
	}

	// Check whether read all faces
	if (nfaces != this->nfaces) {
		fprintf(stderr, "Expected %d faces, but read only %d faces in file %s\n", nfaces, this->nfaces, filename);
	}

	// Close file
	fclose(fp);

	this->center = computeMeshCenter();
	centrateMesh();

	// Exit ok
	return 0;
}



////////////////////////////////////////////////////////////
// PLY FILE READING CODE
////////////////////////////////////////////////////////////

void
	PrintStats(Mesh *mesh)
{
	// Compute bounding box
	float xmin = 1.0E30f, ymin = 1.0E30f, zmin = 1.0E30f;
	float xmax = -1.0E30f, ymax = -1.0E30f, zmax = -1.0E30f;
	for (int i = 0; i < mesh->nverts; i++) {
		Vertex& v = mesh->verts[i];
		if (v.x < xmin) xmin = v.x;
		if (v.y < ymin) ymin = v.y;
		if (v.z < zmin) zmin = v.z;
		if (v.x > xmax) xmax = v.x;
		if (v.y > ymax) ymax = v.y;
		if (v.z > zmax) zmax = v.z;
	}

	// Coont triangles, quads, others
	int ntris = 0, nquads = 0, ngons = 0;
	for (int i = 0; i < mesh->nfaces; i++) {
		Face& f = mesh->faces[i];
		if (f.nverts == 3) ntris++;
		else if (f.nverts == 4) nquads++;
		else ngons++;
	}

	// Print mesh stats
	printf("# Vertices = %d\n", mesh->nverts);
	printf("# Faces = %d ( %d %d %d )\n", mesh->nfaces, ntris, nquads, ngons);
	printf("Bounding box = %g %g   %g %g   %g %g\n", xmin, xmax, ymin, ymax, zmin, zmax);
}

// Compute Mesh Center (and also radius)
Vector3D Mesh::computeMeshCenter()
{
	Vector3D center;
	// Compute bounding box
	float xmin = 1.0E30f, ymin = 1.0E30f, zmin = 1.0E30f;
	float xmax = -1.0E30f, ymax = -1.0E30f, zmax = -1.0E30f;
	for (int i = 0; i < nverts; ++i)
	{
		Vertex& v = verts[i];
		if (v.x < xmin) xmin = v.x;
		if (v.y < ymin) ymin = v.y;
		if (v.z < zmin) zmin = v.z;
		if (v.x > xmax) xmax = v.x;
		if (v.y > ymax) ymax = v.y;
		if (v.z > zmax) zmax = v.z;
	}
	center.x = (xmax + xmin) / 2;
	center.y = (ymax + ymin) / 2;
	center.z = (zmax + zmin) / 2;

	// Also compute radius
	radius = std::max(std::max((xmax - xmin) / 2, (ymax - ymin) / 2), (zmax - zmin) / 2);
	return center;
}

// Centrate Mesh to (0, 0, 0)
void Mesh::centrateMesh()
{
	for (int i = 0; i < nverts; ++i)
	{
		verts[i].x -= center.x;
		verts[i].y -= center.y;
		verts[i].z -= center.z;
	}
}

// Initialize Mesh
void Mesh::Init(const char *filename)
{
	int err_code = ReadOffFile(filename);
	if (err_code != 0)
	{
		std::cerr << "Could not parse file " << filename << "\n";
	}
}