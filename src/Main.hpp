#ifndef MAIN_H
#define MAIN_H

enum ViewMode{ TEST, SPLASH }; // add views here as needed

class Main{
    static Main*_instance;
    ViewMode _viewMode;
    
public:
    static const size_t kWindowWidth;
    static const size_t kWindowHeight;
    static const std::string kName;

    Main();

    static Main*getInstance();
    
    void main();
    void setView(ViewMode v);
};

#endif
