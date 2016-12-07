select Country.Name, Country.Population, Country.SurfaceArea
from 
  Country 
  left join (City inner join Capital on City.CountryCode = Capital.CountryCode) 
  on Country.Code = City.CountryCode
group by City.CountryCode
having City.Population = max(City.Population) and City.Id != Capital.CityId
order by 1.0*(Country.Population)/Country.SurfaceArea desc;
