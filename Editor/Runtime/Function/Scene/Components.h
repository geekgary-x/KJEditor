#pragma once
#include <osg/Vec3>
#include <osg/Matrix>
#include <string>
namespace Soarscape
{
	struct TransformComponent
	{
		osg::Vec3 Translation = { 0.0f, 0.0f, 0.0f };
		osg::Vec3 Rotation = { 0.0f, 0.0f, 0.0f };
		osg::Vec3 Scale = { 1.0f, 1.0f, 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const osg::Vec3& translation)
			: Translation(translation) {}

		osg::Matrix GetTransform() const
		{
			osg::Quat xQuat(Rotation.x(), osg::Vec3(1, 0, 0));
			osg::Quat yQuat(Rotation.y(), osg::Vec3(0, 1, 0));
			osg::Quat zQuat(Rotation.z(), osg::Vec3(0, 0, 1));
			return osg::Matrix::translate(Translation) * osg::Matrix::rotate(xQuat) \
				* osg::Matrix::rotate(yQuat) * osg::Matrix::rotate(zQuat) * osg::Matrix::scale(Scale);
		}
	};

	struct TagComponent
	{
		std::string Tag;
		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};
}