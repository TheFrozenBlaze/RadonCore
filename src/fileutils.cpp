#include <fileutils.h>
#include <fstream>
#include <cstring>



int InputTextCallback(ImGuiInputTextCallbackData* data)
{
    if (data->EventFlag == ImGuiInputTextFlags_CallbackResize)
    {
        auto* buf = (std::vector<char>*)data->UserData;
        buf->resize(data->BufSize);
        data->Buf = buf->data();
    }
    return 0;
}

bool LoadFileToBuffer(const char* path, std::vector<char>& buffer)
{
    std::ifstream ifs(path, std::ios::binary);
    if (!ifs) return false;
    std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
    buffer.assign(content.begin(), content.end());
    buffer.push_back('\0');
    return true;
}

bool SaveBufferToFile(const char* path, const std::vector<char>& buffer)
{
    std::ofstream ofs(path, std::ios::binary);
    if (!ofs) return false;
    ofs.write(buffer.data(), strlen(buffer.data()));
    return ofs.good();
}
