#pragma once

struct Model;

class Table 
{
public :
	bool ChangeMesh = false;

	//std::vector<Model*> ModelMesh;
	//std::vector<Model*> ModelTexture;

	void CreateTableModelMesh(Model* Mesh1, Model* Mesh2, int size);
	void SetTableModelMesh(Model* Mesh1, Model* Mesh2);
};