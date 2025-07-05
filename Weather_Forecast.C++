#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <cstdlib>

class WeatherApp {
private:
    struct WeatherData {
        std::string city;
        float temperature;
        int humidity;
        float windSpeed;
        std::string conditions;
        int airQuality;
    };

     WeatherData generateWeather(const std::string& city) {
        std::srand(std::time(0) + std::hash<std::string>{}(city));
        
        WeatherData data;
        data.city = city;
        data.temperature = 5.0 + (std::rand() % 35); 
        data.humidity = 20 + (std::rand() % 70); 
        data.windSpeed = 1.0 + (std::rand() % 15) / 2.0; 
        data.airQuality = 10 + (std::rand() % 200); 

        if (data.temperature > 30) {
            const std::vector<std::string> hotConditions = {"Sunny", "Heat Wave", "Clear Sky"};
            data.conditions = hotConditions[std::rand() % hotConditions.size()];
        } else if (data.humidity > 70) {
            const std::vector<std::string> humidConditions = {"Rainy", "Foggy", "Overcast"};
            data.conditions = humidConditions[std::rand() % humidConditions.size()];
        } else {
            const std::vector<std::string> normalConditions = {"Partly Cloudy", "Breezy", "Clear"};
            data.conditions = normalConditions[std::rand() % normalConditions.size()];
        }

        return data;
    }

    std::string getAirQualityStatus(int aqi) {
        if (aqi <= 70) return "Good";
        if (aqi <= 140) return "Moderate";
        if (aqi <= 200) return "Unhealthy for Sensitive Groups i.e, older citizens";
        if (aqi <= 260) return "Unhealthy";
        if (aqi <= 350) return "Very Unhealthy";
        return "Hazardous";
    }

    std::vector<std::string> getCityInputs() {
        std::vector<std::string> cities;
        std::string input;

        std::cout << "Enter city names: ";// we can take atleast 3 to4 cities names then we will get the output and after entering the name,each name should be after comma i.e, Delhi, London.Else the resule will be wrong. 
        std::getline(std::cin, input);

        std::stringstream ss(input);
        std::string city;

        while (std::getline(ss, city, ',')) {
           
            city.erase(0, city.find_first_not_of(" \t\n\r\f\v"));
            city.erase(city.find_last_not_of(" \t\n\r\f\v") + 1);
            
            if (!city.empty()) {
                cities.push_back(city);
            }
        }

        return cities;
    }

    void displayWeatherReports(const std::vector<WeatherData>& reports) {
        std::cout << "\nWEATHER REPORT DETAILS:-\n\n";
        
        for (const auto& report : reports) {
            std::cout << "City: " << report.city << "\n";
            std::cout << std::string(30, '-') << "\n";
            std::cout << std::left << std::setw(25) << "Temperature:" 
                      << std::fixed << std::setprecision(1) 
                      << report.temperature << " °C\n";
            std::cout << std::left << std::setw(25) << "Humidity:" 
                      << report.humidity << " %\n";
            std::cout << std::left << std::setw(25) << "Wind Speed:" 
                      << std::setprecision(1) << report.windSpeed << " m/s\n";
            std::cout << std::left << std::setw(25) << "Conditions:" 
                      << report.conditions << "\n";
            std::cout << std::left << std::setw(25) << "Air Quality Index:" 
                      << report.airQuality << " (" 
                      << getAirQualityStatus(report.airQuality) << ")\n";
            std::cout << std::string(30, '-') << "\n\n";
        }

        std::cout << "AQI Guide: 0-50 Good | 51-100 Moderate\n";
        std::cout << "101-150 Unhealthy for Sensitive Groups | 151-200 Unhealthy\n";
        std::cout << "201-300 Very Unhealthy | 301+ Hazardous\n";
    }

public:
    void run() {
        try {
            std::vector<std::string> cities = getCityInputs();
            
            if (cities.size() < 2) {
                throw std::runtime_error("Please enter at proper details of cities");// All the details of that cities will be calculated.
            }

            std::vector<WeatherData> weatherReports;
            for (const auto& city : cities) {
                weatherReports.push_back(generateWeather(city));
            }

            displayWeatherReports(weatherReports);

        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
            std::cerr << "Please try again.\n";
        }
    }
};

int main() {
    WeatherApp app;
    app.run();
    return 0;
}
