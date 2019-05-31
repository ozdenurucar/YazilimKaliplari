namespace Common
{
    class Sensor
    {
    public:
        virtual double GetOutput() const = 0;
        virtual ~Sensor() {};
    };
}
namespace Simplesensors
{
    class ultrasonic : public Common::Sensor
    {
    /*Ultrasonik sensörler dışarıya bir ses dalgası sinyali gönderirler. Gönderdikleri ses dalgasının bir cisme ulaşıp kendisine geri dönmesini beklerler. Sinyalin gönderilip tekrar geri gelme süresi baz alınarak sensörün cisme olan uzaklığı hesaplanır*/
    public:
        ultrasonic(double _velocity, double _time);
        virtual double GetOutput() const;

    private:
        double velocity; //speed of sound
        double time;
    };
}
double ultrasonic::GetOutput() const
    {
        return velocity * time;
    }
 class IRSensors : public Common::Sensor
    {
    /*Ultrasonik sensörler dışarıya bir ses dalgası sinyali gönderirler. Gönderdikleri ses dalgasının bir cisme ulaşıp kendisine geri dönmesini beklerler. Sinyalin gönderilip tekrar geri gelme süresi baz alınarak sensörün cisme olan uzaklığı hesaplanır*/
    public:
        IRSensors();
        virtual double GetOutput() const;
    };
}
class SensorFactory
{    
public:
    enum SENSOR_FACTORIES
    {
        TexasInstruments,
        BroadcomLimited,
        Stmicroelectronics
    };

    virtual ultrasonic* Getultrasonic() = 0;
    virtual IRSensors* GetIRSensors() = 0;

    static SensorFactory* CreateFactory(SENSOR_FACTORIES factory);    
};

//CPP File
SensorFactory* SensorFactory::CreateFactory(SENSOR_FACTORIES factory)
{
    if(factory == SENSOR_FACTORIES::TexasInstruments)
    {
        return new TexasInstrumentsFactory();
    }
    else if(factory == SENSOR_FACTORIES::BroadcomLimited)
    {
        return new BroadcomLimitedFactory();
    }
    else if(factory == SENSOR_FACTORIES::Stmicroelectronics)
    {
        return new StmicroelectronicsFactory();
    }
}
class TexasInstrumentsFactory : public SensorFactory
{
public:
    ultrasonic* Getultrasonic()
    {
    }
    IRSensors* GetIRSensors()
    {
    }
}
class BroadcomLimitedFactory : public SensorFactory
{
public:
    ultrasonic* Getultrasonic()
    {
        return new GalaxyS2();
    }
    IRSensors* GetIRSensors()
    {
        return new Primo();
    }
}
class StmicroelectronicsFactory : public SensorFactory
{
public: 
    ultrasonic* Getultrasonic()
    {
    }
    IRSensors* GetIRSensors()
    {
    }
}
int main(int argc, char* argv[])
{
SensorFactory *factory = SensorFactory::CreateFactory
                (SensorFactory::SENSOR_FACTORIES::TexasInstruments);

    cout << "IR sensor  from Texas Instruments: " << factory->GetIRSensors()->Name() << "\n";
    delete factory->GetIRSensors();
    cout << "ultrasonic sensor from Texas Instruments: " << factory->Getultrasonic()->Name() << "\n";
    delete factory->Getultrasonic();
    delete factory;
    getchar();
    factory = SensorFactory::CreateFactory(SensorFactory::SENSOR_FACTORIES::StmicroelectronicsFactory);
    cout << "IR sensor  from  StmicroelectronicsFactory: " << factory->GetIRSensors()->Name() << "\n";
    delete factory->GetIRSensors();
    cout << "ultrasonic sensor  from Stmicroelectronics: " << factory->Getultrasonic()->Name() << "\n";
    delete factory->Getultrasonic();
    delete factory;
    getchar();
    return 0;
}