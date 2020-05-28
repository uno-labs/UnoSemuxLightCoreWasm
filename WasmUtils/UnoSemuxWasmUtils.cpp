#include "UnoSemuxWasmUtils.hpp"

namespace UnoSemux {

emscripten::val WasmExceptionCatcher(std::function<emscripten::val()> aFn)
{
	emscripten::val returnVal = emscripten::val::object();
	returnVal.set("error", emscripten::val::undefined());

	try
	{
		returnVal.set("res", emscripten::val(aFn()));
	} catch (const std::exception& e)
	{
		returnVal.set("error", std::string(e.what()));
	} catch (...)
	{
		returnVal.set("error", emscripten::val(std::string("Unknown exception")));
	}

	return returnVal;
};

}//namespace UnoSemux
