#include "tensorflow/cc/client/client_session.h"
#include "tensorflow/cc/ops/standard_ops.h"

using namespace tensorflow;
using namespace tensorflow::ops;
using namespace std;

int main()
{
    auto root = Scope::NewRootScope();
    auto x = Variable(root, {}, DataType::DT_INT32);
    auto assign_x = Assign(root, x, 3); // initializer for x
    auto y = Variable(root, {2, 3}, DataType::DT_FLOAT);
    auto assign_y = Assign(root, y, RandomNormal(root, {2, 3}, DataType::DT_FLOAT)); // initializer for y
    auto p_session = new ClientSession(root);
    p_session->Run({assign_x, assign_y}, nullptr); // initialize
    vector<Tensor> outputs;
    p_session->Run({x, y}, &outputs);
    LOG(INFO) << "x = " << outputs[0].scalar<int>();
    LOG(INFO) << "y = " << outputs[1].matrix<float>();
    delete p_session;
    return 0;
}
