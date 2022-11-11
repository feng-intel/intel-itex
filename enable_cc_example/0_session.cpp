#include "tensorflow/cc/client/client_session.h"

using namespace tensorflow;

int main()
{
    auto root = Scope::NewRootScope();
    auto p_session = new ClientSession(root);
    delete p_session;
    return 0;
}
