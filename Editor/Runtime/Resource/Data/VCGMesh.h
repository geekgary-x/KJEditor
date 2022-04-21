#pragma once
#include <vcg/complex/complex.h>
#include <vector>
namespace Soarscape
{
    class VCGVertex;
    class VCGEdge;
    class VCGFace;
    struct VCGUsedTypes : public vcg::UsedTypes<vcg::Use<VCGVertex>::AsVertexType,
                                               vcg::Use<VCGEdge>::AsEdgeType,
                                               vcg::Use<VCGFace>::AsFaceType>
    {
    };

    class VCGVertex : public vcg::Vertex<VCGUsedTypes, vcg::vertex::Coord3f, vcg::vertex::BitFlags, vcg::vertex::Normal3f, vcg::vertex::Mark, vcg::vertex::Color4b>
    {
    };
    class VCGFace : public vcg::Face<VCGUsedTypes, vcg::face::VertexRef,vcg::face::FFAdj, vcg::face::Mark, vcg::face::BitFlags, vcg::face::Normal3f>
    {
    };
    class VCGEdge : public vcg::Edge<VCGUsedTypes>
    {
    };

    typedef vcg::tri::TriMesh<std::vector<VCGVertex>, std::vector<VCGEdge>, std::vector<VCGFace>> BaseTriMesh;

    class VCGMesh
    {
    private:
        BaseTriMesh m_Mesh;
    public:
        VCGMesh() = default;
        void ReadFile(const std::string&);
    };

} // namespace kanjing
