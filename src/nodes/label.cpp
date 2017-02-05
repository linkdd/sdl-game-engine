#include <sge/nodes/label.hpp>
#include <sge/engine.hpp>
#include <iostream>

using namespace std;

namespace sge
{
    vector<string> LabelNode::mro() const
    {
        auto _mro = PositionNode::mro();
        _mro.push_back("LabelNode");
        return _mro;
    }

    void LabelNode::set_font(const string &assetname)
    {
        FontDescriptor d(assetname);

        if (font == nullptr)
        {
            font = engine.assets().load<Font>(d);
        }
        else if (font->descriptor()->name() != d.name())
        {
            font.reset();
            font = engine.assets().load<Font>(d);
        }
    }

    void LabelNode::set_text(const string &text)
    {
        content = text;
    }

    void LabelNode::set_color(SDL_Color fg)
    {
        color = fg;
    }

    void LabelNode::ready()
    {
        set_draw(true);
    }

    void LabelNode::draw()
    {
        if (font == nullptr || content.empty())
        {
            return;
        }

        if (!engine.renderer().draw_text(font, content, get_absolute_pos(), color))
        {
            cerr << "[LabelNode][ERROR] " << engine.renderer().get_error() << endl;
        }
    }
}
