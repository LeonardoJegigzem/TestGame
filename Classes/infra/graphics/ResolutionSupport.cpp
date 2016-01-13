#include "infra/graphics/ResolutionSupport.h"

void ResolutionSupport::setScalingResolution(GLView* openGLView)
{
    openGLView->setDesignResolutionSize(427, 240, ResolutionPolicy::NO_BORDER); /// Escala la imagen sin perder el aspect ratio ;)


    /** Hay que calcular el scaleContentFactor según el tamaño del fondo! */
}
