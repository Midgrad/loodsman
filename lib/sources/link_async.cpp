#include "link_async.h"

using namespace loodsman;

void LinkAsync::LinkAsync::checkHandlers()
{
    m_ioContext.poll();
    m_ioContext.reset();
}

void LinkAsync::LinkAsync::runHandlers()
{
    m_ioContext.run();
}
