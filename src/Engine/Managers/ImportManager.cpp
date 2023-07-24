
#include "ImportManager.h"

Mesh *Import(const char *path)
{
      std::vector<float> vertices;
      std::vector<unsigned int> indices;

      Assimp::Importer importer;
      const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

      /****************
      implement 3d-mesh loader
      ****************/

      return new Mesh();
}
