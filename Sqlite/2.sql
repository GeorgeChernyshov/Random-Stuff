select Country.Name, max(LiteracyRate.Rate)
from 
  Country inner join LiteracyRate on Country.Code = LiteracyRate.CountryCode;

