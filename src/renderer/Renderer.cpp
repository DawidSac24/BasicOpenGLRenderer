#include "Renderer.h"

namespace Renderer
{
void Renderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader)
{
    shader.bind();
    va.bind();
    ib.bind();
    // We specify the count as the number of INDICES not vertexes!!!
    // don't have to reference the indices bc we did it in glBind (so we put nullptr)
    glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

} // namespace Renderer
