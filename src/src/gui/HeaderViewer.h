#pragma once
namespace debug {
class HeaderViewer 
{
  public:
    bool m_show = false;
    void draw();
    void setPbpHeader(std::string header);
    void setPSFHeader(std::string header);

  private:
    std::string pbpheader;
    std::string psfheader;
};
}  // namespace debug
