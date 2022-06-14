#pragma once
namespace debug {
class HeaderViewer 
{
  public:
    bool m_show = false;
    void draw();
    void setPbpHeader(std::string header);

  private:
    std::string pbpheader;
};
}  // namespace debug
