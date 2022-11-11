#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/standard_ops.h"

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace std;

int main()
{
    auto root = Scope::NewRootScope();
    auto w = Const(root, 2, {});
    auto p_session = new ClientSession(root);
    vector<Tensor> outputs;
    p_session->Run({w}, &outputs);
    LOG(INFO) << "w = " << outputs[0].scalar<int>();
    delete p_session;
    return 0;
}
