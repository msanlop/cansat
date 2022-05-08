#pragma once

// include I2C library + Wire?

class Lora
{
    public:
        Lora();
        void transferData(vector<vector<double>>, vector<unsigned long>);
        void confirmSetup(unsigned long time);
        void confirmLaunch(unsigned long time);
};