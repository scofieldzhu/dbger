#include "standardFormatter.h"
#include "log.h"
#include "xtime.h"
#include "xText.h"
#include "level.h"
using namespace std;
USING_LGT

DGR2_NP_BEGIN

void StandardFormatter::format(Log& log)
{
    xStrT result = XT("");
    handleLineBreak(log, result);
    result += XT("[");    
    result += log.getTimeStamp().repr();
    result += XT("][");
    result += log.getLevel().repr();
    result += XT("][");
    result += log.getFileName();
    result += XT("(");
    result += Int2Str(log.getLineNo());    
    result += XT(")]:");
    if (!log.getContent().empty())
        result += log.getContent();
    log.setContent(result);
}

void StandardFormatter::handleLineBreak(Log& log, xStrT& formatted_str)
{
    if (log.getContent().empty())
        return;
    xStrT::size_type pos = 0;
    xStrT content_copy = log.getContent();
    for (; pos != xStrT::npos; ++pos)
    {
        if (content_copy[pos] != 13 && content_copy[pos] != 10)
            break;
    }
    if (pos != 0)
    {
        formatted_str = content_copy.substr(0, pos);
        log.setContent(content_copy.substr(pos));
    }
}

StandardFormatter::StandardFormatter()
{

}

StandardFormatter::~StandardFormatter()
{

}

NP_END