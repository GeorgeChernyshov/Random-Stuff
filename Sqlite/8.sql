select Country.Name, City.Name
from
  Country
  left join (City inner join Capital on City.Id = Capital.CityId)
  on Country.Code = City.CountryCode
group by Country.Code
having City.Population < max(City.Population);
