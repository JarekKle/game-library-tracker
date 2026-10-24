#pragma once

class HomeView{
    private:
        int mSelectedOption = 0;
    public:
        HomeView();
        void displayHomeView();
        int getUserChoice();
};