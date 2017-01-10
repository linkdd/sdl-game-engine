#ifndef __SGE_TILEMAP_NODE_HPP
#define __SGE_TILEMAP_NODE_HPP

#include <sge/nodes/position.hpp>
#include <sge/assets/loaders/image.hpp>
#include <sge/assets/loaders/json.hpp>

namespace sge
{
    class TileMapNode : public PositionNode
    {
        using PositionNode::PositionNode;

        public:
            virtual std::vector<std::string> mro() const;

            void set_tilemap(const std::string &assetname);
            
            SDL_Rect get_viewport() const;
            void set_viewport(SDL_Rect vport);
            void set_viewport(int x, int y, int w, int h);

            virtual void ready();
            virtual void draw();

        private:
            std::shared_ptr<Image> tileset;
            std::shared_ptr<JSON> tilemap;
            SDL_Rect viewport;
    };
}

#endif /* __SGE_TILEMAP_NODE_HPP */
