#include "chronotext/incubator/ui/Button.h"
#include "chronotext/text/FontHelper.h"
#include "chronotext/utils/GraphicHelper.h"
#include "chronotext/utils/Utils.h"

using namespace ci;
using namespace std;

namespace chronotext
{
    Button::Button(ButtonStyleRef style)
    :
    Shape(style),
    Touchable(this, TYPE_CLICKABLE, style->hitExtra),
    style(style),
    delegate(NULL)
    {}

    float Button::getWidth()
    {
        if (autoWidth)
        {
            return paddingLeft + getContentWidth() + paddingRight;
        }
        else
        {
            return width;
        }
    }
    
    float Button::getHeight()
    {
        if (autoHeight)
        {
            return paddingTop + getContentHeight() + paddingBottom;
        }
        else
        {
            return height;
        }
    }
    
    void Button::draw()
    {
        float x1 = x;
        float y1 = y;
        float x2 = x1 + getWidth();
        float y2 = y1 + getHeight();
        
        float inset = 0;
        
        if (style->borderColor[state])
        {
            inset = 1;
            
            gl::color(*style->borderColor[state]);
            GraphicHelper::fillBox(x1, y1, x2, y2);
        }
        
        if (style->backgroundColor[state])
        {
            gl::color(*style->backgroundColor[state]);
            GraphicHelper::fillBox(x1 + inset, y1 + inset, x2 - inset, y2 - inset);
        }
        
        // ---
        
        gl::color(*style->color[state]);
        
        if (icon)
        {
            glPushMatrix();
            glTranslatef(x1 + (x2 - x1) * 0.5, y1 + (y2 - y1) * 0.5, 0);
            glScalef(icon->scale, icon->scale, 1);
            
            icon->texture->begin();
            icon->texture->drawFromCenter();
            icon->texture->end();
            
            glPopMatrix();
        }
        else
        {
            style->font->setSize(style->fontSize);
            FontHelper::drawTextInRect(style->font, NULL, text, x1, y1, x2, y2, style->snap);
            
            if (style->strikethrough[state])
            {
                FontHelper::drawStrikethroughInRect(style->font, text, x1, y1, x2, y2, style->snap);
            }
        }
    }
    
    float Button::getContentWidth()
    {
        if (icon)
        {
            return icon->getWidth();
        }
        else
        {
            style->font->setSize(style->fontSize);
            return FontHelper::getStringWidth(style->font, text, style->snap);
        }
    }
    
    float Button::getContentHeight()
    {
        if (icon)
        {
            return icon->getHeight();
        }
        else
        {
            style->font->setSize(style->fontSize);
            return style->font->getHeight();
        }
    }
    
    std::vector<Touchable*> Button::getTouchables()
    {
        vector<Touchable*> touchables;
        touchables.push_back(this);
        return touchables;
    }
    
    void Button::touchStateChanged(Touchable *touchable, int state)
    {}
    
    void Button::touchActionPerformed(Touchable *touchable, int action)
    {
        if (delegate)
        {
            if (action == Touchable::ACTION_CLICKED)
            {
                delegate->buttonClicked(tag);
            }
            else if (action == Touchable::ACTION_TOGGLED)
            {
                delegate->buttonToggled(tag);
            }
        }
    }
    
    bool Button::hitTest(const Vec2f &point, float *distance)
    {
        Rectf extra = getBounds().inflated(Vec2f(hitExtra, hitExtra));
        
        if (extra.contains(point))
        {
            *distance = getBounds().distance(point);
            return true;
        }
        
        return false;
    }
}
