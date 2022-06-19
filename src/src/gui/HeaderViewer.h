#pragma once
namespace debug {
class HeaderViewer 
{
  public:
    bool m_show = false;
    void draw();
    void setPbpHeader(std::string header);
    void setPSFHeader(std::string header);
    void setElfHeader(std::string header);
    void setElfPHeader(std::string header);
    void setElfSHeader(std::string header);
  private:
    std::string pbpheader;
    std::string psfheader;
    std::string elfheader;
    std::string elfPheader;
    std::string elfSheader;
};
}  // namespace debug
