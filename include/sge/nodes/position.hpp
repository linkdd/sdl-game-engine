#ifndef __SGE_POSITION_NODE_HPP
#define __SGE_POSITION_NODE_HPP

#include <sge/node.hpp>
#include <sge/utils/matrix.hpp>
#include <sge/utils/vector.hpp>

namespace sge
{
    class PositionNode : public Node
    {
        using Node::Node;

        public:
            virtual std::vector<std::string> mro() const;

            Vector get_pos() const;
            void set_pos(const Vector &pos);
            void set_pos(int x, int y);

            float get_rotation() const;
            void set_rotation(float angle);

            Vector get_absolute_pos() const;
            float get_absolute_rotation() const;

            Matrix<3,3> get_pm_transform() const;

        private:
            void pre_multiply_transform();

        private:
            Vector _pos;
            float _angle = 0;

            Matrix<3,3> translation;
            Matrix<3,3> rotation;
            Matrix<3,3> pm_transform;
    };
}

#endif /* __SGE_POSITION_NODE_HPP */
