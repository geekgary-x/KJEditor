#include "Resource/Data/VCGMesh.h"
#include "Core/Base/macro.h"
#include <wrap/io_trimesh/import_obj.h>
#include <wrap/io_trimesh/import_ply.h>
namespace Soarscape
{
	void VCGMesh::readFile(const std::string& filename)
	{
        auto pointPos = filename.find_last_of(".");
        auto lPos = filename.find_last_of("/");
        std::string meshName = filename.substr(lPos + 1, pointPos - 1 - lPos);
        std::string extendName = filename.substr(pointPos + 1);
        LOG_INFO("mesh Name = {0}", meshName);
        LOG_INFO("mesh extenName = {0}", extendName);
        if (extendName == "obj")
        {
            vcg::tri::io::ImporterOBJ<BaseTriMesh>::Info info;
            if ((vcg::tri::io::ImporterOBJ<BaseTriMesh>::Open(m_Mesh, filename.c_str(), info) == vcg::tri::io::ImporterOBJ<BaseTriMesh>::E_NOERROR))
            {
                LOG_INFO("Input mesh: {0}", meshName);
                LOG_INFO("Mesh file type: {0}", extendName);
            }
            else
            {
                LOG_ERROR("Can't read FIle : {0}", filename);
            }
        }
        else if (extendName == "ply")
        {
            if (vcg::tri::io::ImporterPLY<BaseTriMesh>::Open(m_Mesh, filename.c_str()) == 0)
            {
                LOG_INFO("Input mesh: {0}", meshName);
                LOG_INFO("Mesh file type: {0}", extendName);
            }
            else
            {
                LOG_INFO("Can't read FIle : {0}", filename);
            }
        }

        else
        {
            LOG_ERROR("Editor can't suport format :{0}", extendName);
        }
	}
}