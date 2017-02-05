#ifndef __SGE_LABEL_NODE_HPP
#define __SGE_LABEL_NODE_HPP

#include <sge/nodes/position.hpp>
#include <sge/assets/loaders/font.hpp>

namespace sge
{
    class LabelNode : public PositionNode
    {
        using PositionNode::PositionNode;

        public:
            virtual std::vector<std::string> mro() const;

            void set_font(const std::string &assetname);
            void set_text(const std::string &text);
            void set_color(SDL_Color color);

            virtual void ready();
            virtual void draw();

        private:
            std::shared_ptr<Font> font;
            std::string content;
            SDL_Color color;
    };
}

#endif /* __SGE_LABEL_NODE_HPP */
