#ifndef YAMI_MODEL_GENERATOR_H
#define YAMI_MODEL_GENERATOR_H

#include "../Core/Scene/MeshConfig.h"
#include "../Core/Scene/Model.h"
#include "../Maths/Maths.h"

#include <vector>

namespace yami
{
	class ModelGenerator
	{
	public:
		static Model* generateTriangle()
		{
			std::vector<Mesh*> meshes;
			meshes.push_back(new Mesh());

			meshes[0]->vertices.push_back({ {0.0f, 0.5f, 0.0f}, {0.0f, 0.0f, -1.0f} });
			meshes[0]->vertices.push_back({{ -0.5f, -0.5f, 0.0f },{ 0.0f, 0.0f, -1.0f } });
			meshes[0]->vertices.push_back({{ 0.5f, -0.5f, 0.0f },{ 0.0f, 0.0f, -1.0f } });

			meshes[0]->indices = {0, 1, 2};
			meshes[0]->uploadToGPU();
			return new Model(meshes);
		}

		static Model* generateQuad(const Vec3& offset, const Vec3& normal, float size = 1.0f, unsigned int resolution = 1)
		{
			std::vector<Mesh*> meshes;
			meshes.push_back(new Mesh());
			
			if (resolution == 1)
			{
				Quaternion normalRotation(Vec3(0.0f, 0.0f, 1.0f), normal);
				Vec3 up = normalRotation * Vec3(0.0f, 1.0f, 0.0f);
				Vec3 right = normalRotation * Vec3(1.0f, 0.0f, 0.0f);
				meshes[0]->vertices.push_back({ -right * size - up * size + offset, normal });
				meshes[0]->vertices.push_back({ -right * size + up * size + offset, normal });
				meshes[0]->vertices.push_back({ right * size + up * size + offset, normal });
				meshes[0]->vertices.push_back({ right * size - up * size + offset, normal });
				meshes[0]->indices = { 0, 3, 1, 1, 3, 2 };
			}
			else
			{
				float squareSize = size / (float)resolution;
				float sqSize = 0.5f*squareSize;
				float sqOffset = -(((float)resolution - 1.0f) / 2.0f)*squareSize;
				Quaternion normalRotation(Vec3(0.0f, 0.0f, 1.0f), normal);
				Vec3 up = normalRotation * Vec3(0.0f, 1.0f, 0.0f);
				Vec3 right = normalRotation * Vec3(1.0f, 0.0f, 0.0f);
				for (unsigned int y = 0; y < resolution; y++)
				{
					for (unsigned int x = 0; x < resolution; x++)
					{
						float xOffset = x * squareSize;
						float yOffset = y * squareSize;
						meshes[0]->vertices.push_back({ -right * sqSize + right * (sqOffset + xOffset) - up * sqSize + up * (sqOffset + yOffset) + offset, normal });
						meshes[0]->vertices.push_back({ -right * sqSize + right * (sqOffset + xOffset) + up * sqSize + up * (sqOffset + yOffset) + offset, normal });
						meshes[0]->vertices.push_back({ right * sqSize + right * (sqOffset + xOffset) + up * sqSize + up * (sqOffset + yOffset) + offset, normal });
						meshes[0]->vertices.push_back({ right * sqSize + right * (sqOffset + xOffset) - up * sqSize + up * (sqOffset + yOffset) + offset, normal });

						unsigned int index = (x + y * resolution) * 4;
						meshes[0]->indices.push_back(index);
						meshes[0]->indices.push_back(index + 3);
						meshes[0]->indices.push_back(index + 1);
						meshes[0]->indices.push_back(index + 1);
						meshes[0]->indices.push_back(index + 3);
						meshes[0]->indices.push_back(index + 2);
					}
				}
			}

			meshes[0]->uploadToGPU();
			return new Model(meshes);
		}

		static Model* generateBox(float size = 1.0f, unsigned int resolution = 1)
		{
			std::vector<Mesh*> meshes;
			meshes.push_back(new Mesh());

			if (resolution == 1)
			{
				meshes[0]->vertices.push_back({ { -size, -size, size },{ 0.0f, 0.0f, 0.0f } });
				meshes[0]->vertices.push_back({ { -size, size, size },{ 0.0f, 0.0f, 0.0f } });
				meshes[0]->vertices.push_back({ { size, size, size },{ 0.0f, 0.0f, 0.0f } });
				meshes[0]->vertices.push_back({ { size, -size, size },{ 0.0f, 0.0f, 0.0f } });

				meshes[0]->vertices.push_back({ { -size, -size, -size },{ 0.0f, 0.0f, 0.0f } });
				meshes[0]->vertices.push_back({ { -size, size, -size },{ 0.0f, 0.0f, 0.0f } });
				meshes[0]->vertices.push_back({ { size, size, -size },{ 0.0f, 0.0f, 0.0f } });
				meshes[0]->vertices.push_back({ { size, -size, -size },{ 0.0f, 0.0f, 0.0f } });

				meshes[0]->indices = {
					0, 3, 1, 1, 3, 2, // Front
					4, 5, 7, 7, 5, 6, // Back
					0, 5, 4, 5, 0, 1, // Left
					3, 7, 2, 2, 7, 6, // Right
					6, 5, 1, 1, 2, 6, // Up
					7, 0, 4, 7, 3, 0  // Down
				};
			}
			else
			{
				float halfSize = size * 0.5f;
				// Front
				generateAddPlane(meshes[0], Vec3(0.0f, 0.0f, 1.0f), Vec3(0.0f, 0.0f, halfSize), size, resolution);
				// Back
				generateAddPlane(meshes[0], Vec3(0.0f, 0.0f, -1.0f), Vec3(0.0f, 0.0f, -halfSize), size, resolution);
				// Left
				generateAddPlane(meshes[0], Vec3(-1.0f, 0.0f, 0.0f), Vec3(-halfSize, 0.0f, 0.0f), size, resolution);
				// Right
				generateAddPlane(meshes[0], Vec3(1.0f, 0.0f, 0.0f), Vec3(halfSize, 0.0f, 0.0f), size, resolution);
				// Up
				generateAddPlane(meshes[0], Vec3(0.0f, 1.0f, 0.0f), Vec3(0.0f, halfSize, 0.0f), size, resolution);
				// Down
				generateAddPlane(meshes[0], Vec3(0.0f, -1.0f, 0.0f), Vec3(0.0f, -halfSize, 0.0f), size, resolution);
			}
			meshes[0]->uploadToGPU();
			return new Model(meshes);
		}

		static Model* generateSphere(float radius = 0.5f, unsigned int resolution = 1)
		{
			Model* model = generateBox(0.5f, resolution);
			Mesh* mesh = model->getMeshes()[0];

			for (unsigned int i = 0; i < mesh->vertices.size(); i++)
			{
				mesh->vertices[i].normal = yami::Maths::normalize<Vec3>(mesh->vertices[i].position);
				mesh->vertices[i].position = mesh->vertices[i].normal * radius;
			}
			mesh->uploadToGPU();

			return model;
		}

		static Model* generatePlane(float size = 1.0f, const Vec3& normal = Vec3::VEC3_Y)
		{
			std::vector<Mesh*> meshes;
			meshes.push_back(new Mesh());

			Quaternion normalRotation(Vec3(0.0f, 0.0f, 1.0f), normal);
			Vec3 up = normalRotation * Vec3(0.0f, 1.0f, 0.0f);
			Vec3 right = normalRotation * Vec3(1.0f, 0.0f, 0.0f);
			meshes[0]->vertices.push_back({ -right * size - up * size, normal });
			meshes[0]->vertices.push_back({ -right * size + up * size, normal });
			meshes[0]->vertices.push_back({ right * size + up * size, normal });
			meshes[0]->vertices.push_back({ right * size - up * size, normal });
			meshes[0]->indices = { 0, 3, 1, 1, 3, 2 };

			meshes[0]->uploadToGPU();
			return new Model(meshes);
		}

		static Model* generateTerrain(unsigned int side = 4, float squareSize = 1.0f)
		{
			std::vector<Mesh*> meshes;
			meshes.push_back(new Mesh());

			float size = 0.5f*squareSize;
			float offset = -(((float)side - 1.0f) / 2.0f)*squareSize;

			for (unsigned int y = 0; y < side; y++)
			{
				for (unsigned int x = 0; x < side; x++)
				{
					float xOffset = x*squareSize;
					float yOffset = y*squareSize;
					Vec3 normal(0.0f, 1.0f, 0.0f);
					meshes[0]->vertices.push_back({ { -1.0f*size + xOffset + offset, 0.0f, -1.0f*size + yOffset + offset }, normal });
					meshes[0]->vertices.push_back({ { -1.0f*size + xOffset + offset, 0.0f, 1.0f*size + yOffset + offset }, normal });
					meshes[0]->vertices.push_back({ { 1.0f*size + xOffset + offset, 0.0f, 1.0f*size + yOffset + offset }, normal });
					meshes[0]->vertices.push_back({ { 1.0f*size + xOffset + offset, 0.0f, -1.0f*size + yOffset + offset }, normal });

					unsigned int index = (x + y*side)*4;
					meshes[0]->indices.push_back(index);
					meshes[0]->indices.push_back(index+1);
					meshes[0]->indices.push_back(index+3);
					meshes[0]->indices.push_back(index+3);
					meshes[0]->indices.push_back(index+1);
					meshes[0]->indices.push_back(index+2);
				}
			}
			meshes[0]->uploadToGPU();
			return new Model(meshes);
		}

	private:
		static void generateAddPlane(Mesh* mesh, const Vec3& normal, const Vec3& offset, float size, float resolution)
		{
			float squareSize = size / (float)resolution;
			float sqSize = 0.5f*squareSize;
			float sqOffset = -(((float)resolution - 1.0f) / 2.0f)*squareSize;
			Quaternion normalRotation(Vec3(0.0f, 0.0f, 1.0f), normal);
			Vec3 up = normalRotation * Vec3(0.0f, 1.0f, 0.0f);
			Vec3 right = normalRotation * Vec3(1.0f, 0.0f, 0.0f);
			unsigned int baseIndex = mesh->vertices.size();
			for (unsigned int y = 0; y < resolution; y++)
			{
				for (unsigned int x = 0; x < resolution; x++)
				{
					float xOffset = x * squareSize;
					float yOffset = y * squareSize;
					mesh->vertices.push_back({ right * (sqOffset + xOffset - sqSize) + up * (sqOffset + yOffset - sqSize) + offset, normal });
					mesh->vertices.push_back({ right * (sqOffset + xOffset - sqSize) + up * (sqOffset + yOffset + sqSize) + offset, normal });
					mesh->vertices.push_back({ right * (sqOffset + xOffset + sqSize) + up * (sqOffset + yOffset + sqSize) + offset, normal });
					mesh->vertices.push_back({ right * (sqOffset + xOffset + sqSize) + up * (sqOffset + yOffset - sqSize) + offset, normal });

					unsigned int index = baseIndex+(x + y * resolution) * 4;
					mesh->indices.push_back(index);
					mesh->indices.push_back(index + 3);
					mesh->indices.push_back(index + 1);
					mesh->indices.push_back(index + 1);
					mesh->indices.push_back(index + 3);
					mesh->indices.push_back(index + 2);
				}
			}
		}

	};
}

#endif
