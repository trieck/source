
#include <iostream>
#include <string>
#include <windows.h>
#include <tchar.h>
#include <comdef.h>

#import "msxml3.dll"
using namespace MSXML2;

using std::cout;
using std::cerr;
using std::string;
using std::endl;

#include "exception.h"

struct _coinit {
    _coinit() {
        CoInitialize(NULL);
    }
    ~_coinit() {
        CoUninitialize();
    }
} coinit;


namespace {

} // anonymous

/////////////////////////////////////////////////////////////////////////////
int _tmain(int argc, TCHAR *argv[])
{
    try {
        IXMLDOMDocumentPtr doc;

        // Create an instance of the DOMDocument
        HRESULT hr = doc.CreateInstance(__uuidof(DOMDocument));
        if (FAILED(hr))
            throw _com_error(hr);

        _variant_t vtDoc("d:\\source\\xml\\test.xml");

        // Create a processing instruction
        IXMLDOMProcessingInstructionPtr pi =
            doc->createProcessingInstruction("xml", "version=\"1.0\"");

        doc->appendChild(pi);

        variant_t vtChild;
        vtChild.vt = VT_I2;
        vtChild.iVal = NODE_ELEMENT;

        // create the root element
        IXMLDOMNodePtr child = doc->createNode(vtChild, "root", "");
        child->text = "This is some text";

        doc->appendChild(child);

        // Save the document
        hr = doc->save(vtDoc);
        if (FAILED(hr))
            throw(hr);

    } catch (const _com_error & E) {
        cerr << E.ErrorMessage() << endl;
        return 1;
    } catch (const Exception & E) {
        cerr << E.getDescription() << endl;
        return 1;
    }

    return 0;
}

namespace { // anonymous



} // anonymous