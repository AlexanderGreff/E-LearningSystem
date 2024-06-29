class DataBase
{
    private:
        DataBase();

    public:
        DataBase(const DataBase&) = delete;

        static DataBase getInstance()
        {
            static DataBase instance;
            return instance;
        }
};