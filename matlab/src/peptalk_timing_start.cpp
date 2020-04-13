#include <mex.h>
#include "timing.hpp"

using std::string;
using std::vector;

void OnErrorOrWarning(const string &peptalk_msg, const string &papi_msg) {
    mexErrMsgTxt((peptalk_msg + ". " + papi_msg).c_str());
}

vector<string> UnpackCellOfStrings(const mxArray *cell_of_strings) {
    size_t num_string = mxGetNumberOfElements(cell_of_strings);
    vector<string> texts;
    texts.reserve(num_string);
    for (size_t idx = 0; idx < num_string; ++idx) {
        mxArray *text_ptr = mxGetCell(cell_of_strings, idx);
        if (mxIsChar(text_ptr)) {
            texts.emplace_back(mxArrayToString(text_ptr));
        }
    }
    return texts;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[]) {
    if (!mexIsLocked()) {
        mexLock();
    }
    peptalk::timing::Start(UnpackCellOfStrings(prhs[0]), OnErrorOrWarning);
}
