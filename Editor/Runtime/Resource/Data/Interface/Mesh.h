#pragma once
#include <string>
#include <vector>
namespace Soarscape
{
	struct Vertex
	{
        float px;
        float py;
        float pz;
        float nx;
        float ny;
        float nz;
        float u;
        float v;
	};

    class Mesh
    {
    public:
        virtual void readFile(const std::string&);
        virtual void updateRenderObj();
        virtual ~Mesh();
    public:
        uint32_t m_VAO = 0;
        uint32_t m_VBO = 0;
        std::vector<Vertex> m_V;
        std::vector<uint32_t> m_I;
        std::string m_Path;

        bool operator==(const Mesh& other) const { return other.m_Path == m_Path; }
    };
}