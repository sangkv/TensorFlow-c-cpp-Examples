/*
Date: 2021/01/23
Undocumented Tensorflow C API
Link: https://medium.com/@vladislavsd/undocumented-tensorflow-c-api-b527c0b4ef6

Note: If our C program needs to load and use the model, it must be saved in SavedModel format.
No, a single “frozen” model file is not enough*.

The Roadmap
1. Create the computation graph
2. Instantiate/reload a session and associate it with the graph. The trained model is also loaded here.
3. Define graph inputs/outputs
+ Types (e.g. TF_FLOAT as floating number)
+ Shapes
+ Names of nodes
4. Create input tensor(s) and populate with data
5. Run the session
6. Get data from output tensor(s)
*/

//#include <iostream>
//#include <cstring>
#include <tensorflow/c/c_api.h>

//using namespace std;

int main()
{

    // Create a Graph
    TF_Graph * Graph = TF_NewGraph();
    // Create Status
    TF_Status * Status = TF_NewStatus();
    // Create tensorflow session
    TF_SessionOptions * SessionOpts = TF_NewSessionOptions();
    TF_Buffer* RunOpts = NULL;
    //Provide information about the model to be loaded
    const char* save_model_dir = "<path_to_dir_with_saved_model>";
    const char* tags = "serve"; // default model serving tag; can change in future
    int ntags = 1;
    // Initialize a tensorflow session
    TF_Session* Session = TF_LoadSessionFromSavedModel(SessionOpts, RunOpts, save_model_dir, &tags, ntags, Graph, NULL, Status);

    // Define Inputs
    int NumInputs = 2;
    TF_Output* Input = malloc(sizeof(TF_Output) * NumInputs);

    TF_Output t0 = {TF_GraphOperationByName(Graph, "<node0>"), <idx0>};
    TF_Output t1 = {TF_GraphOperationByName(Graph, "<node1>"), <idx1>};

    Input[0] = t0;
    Input[1] = t1;

    // Define Outputs
    int NumOutputs = 1;
    TF_Output* Output = malloc(sizeof(TF_Output) * NumOutputs);

    TF_Output t2 = {TF_GraphOperationByName(Graph, "<node2>"), <idx2>};

    Output[0] = t2;

    // Provide data for inputs & outputs
    TF_Tensor** InputValues = malloc(sizeof(TF_Tensor*)*NumInputs);
    TF_Tensor** OutputValues = malloc(sizeof(TF_Tensor*)*NumOutputs);
    /* create tensors with data here */
    tensor0 = ...;
    tensor1 = ...;
    /* Assign input tensors with the actual data: */
    InputValues[0] = tensor0;
    InputValues[1] = tensor1;

    // Run the Session
    TF_SessionRun (Session, NULL, Input, InputValues, NumInputs, Output, OutputValues, NumOutputs, NULL, 0, Status);


    /* Process outputs tensor*/


    // Freeing Allocated Memory
    TF_DeleteGraph(Graph);
    TF_DeleteSession(Session, Status);
    TF_DeleteSessionOptions(SessionOpts);
    TF_DeleteStatus(Status);

    //cout << "Hello world!" << endl;
    //cout << "Tensorflow Version: " << TF_Version() << endl;
    return 0;
}

//Bonus
/*
//Create a 1-dim tensor holding an integer
int ndims = 1;
int64_t dims[] = {1};
int ndata = sizeof(int32_t);
int32_t data[] = {4};

TF_Tensor* int_tensor = TF_NewTensor(TF_INT32, dims, ndims, data, ndata, NULL, NULL);

// If the tensor must be a scalar (0 dimensions), then:
int64_t dims = NULL;
int ndims = 0;

*/

/*
// Create an array of strings (Attention)
TF_Tensor* str_tensor = TF_NewTensor(TF_String, nstr, ndims, base, bsize, free_array, base);

const char * sarr;
int nstr;

size_t tsize = 0;
for (int i = 0; i <nstr; i ++) {
tsize + = TF_StringEncodedSize (strlen (sarr [i])) + sizeof (TF_DataTypeSize (TF_UINT64)); }

char * base = malloc (sizeof (char) * tsize;
char * start = sizeof (TF_DataTypeSize (TF_UINT64)) * nstr + base;
char * dest = start;
size_t dest_len = tsize - (size_t) (start - base);
uint64_t * offset = (uint64_t *) (base);

for (int i = 0; i <nstr; i ++) {
* offset = (dest - start);
hiệu số ++;
size_t a = TF_StringEncode (sarr [i], strlen (sarr [i]), dest, dest_len, Trạng thái);
dest + = a;
dest_len - = a;
}

int64_t dimvec [] = {1, nstr};
size_t ndims = 2;

TF_Tensor * tarr = TF_NewTensor (TF_STRING, dimvec, ndims, base, tsize, free_array, base);

s = [[“some”, “interesting”, ”data”, “here”]]

*/

/*
// How do I unpack a tensor of strings?
// First, prepare the array of strings:
char** out[];
size_t nout;
// Get the Tensor of strings from the array of output tensors:
TF_Tensor* tout = OutputValues[0]; // assuming we want the first one
// Get shape information of the tensor:
nout = (size_t)TF_Dim(tout, 1)]; // assuming the number of strings is 2nd dim
// Prepare arrays for encoded data and offsets:
void* buff = TF_TensorData(tout);
int64_t* offsets = buff;
// Prepare utility pointers:
char* data = buff + nout * sizeof(int64_t);
char* buff_end = buff + TF_TensorByteSize(tout);
// Allocate pointer to arrays of strings:
*out = calloc(nout, sizeof(char*));
// Decode every string and copy it into the array of strings:
for (int i = 0; i < nout; i++) {
 char* start = buff + offsets[i];
 const char* dest;
 size_t n;
 TF_StringDecode(start, buff_end — start, &dest, &n, Status);
 if (TF_GetCode(Status) == TF_OK) {
 (*out)[i] = malloc(n + 1);
 memcpy((*out)[i], dest, n);
 *((*out)[i] + n) = ‘\0’; }
}
*/
