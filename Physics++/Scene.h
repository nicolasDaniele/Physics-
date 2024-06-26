#pragma once

#include "Geometry3D.h"
#include <vector>

struct OctreeNode
{
	AABB bounds;
	OctreeNode* children;
	std::vector<Model*> models;

	inline OctreeNode() : children(0) { }
	inline ~OctreeNode()
	{
		if (children != 0)
		{
			delete[] children;
		}
	}
};

class Scene
{
public:
	inline Scene() : octree(0) { }
	inline ~Scene()
	{
		if (octree != 0)
		{
			delete octree;
		}
	}

	void AddModel(Model* model);
	void RemoveModel(Model* model);
	void UpdateModel(Model* model); 
	std::vector<Model*> FindChildren(const Model* model);
	Model* Raycast(const Ray& ray);
	std::vector<Model*> Query(const Sphere& sphere);
	std::vector<Model*> Query(const AABB& aabb);
	bool Accelerate(const Vec3& position, float size);
	std::vector<Model*> Cull(const Frustum& frustum);

protected:
	std::vector<Model*> objects;
	OctreeNode* octree;

private:
	Scene(const Scene&);
	Scene& operator=(const Scene&);
};

void SplitTree(OctreeNode* node, int depth);
void Insert(OctreeNode* node, Model* model);
void Remove(OctreeNode* node, Model* model);
void Update(OctreeNode* node, Model* model);
Model* FindClosest(const std::vector<Model*>& set, const Ray& ray);
Model* Raycast(OctreeNode* node, const Ray& ray);
std::vector<Model*> Query(OctreeNode* node, const Sphere& sphere);
std::vector<Model*> Query(OctreeNode* node, const AABB& aabb);