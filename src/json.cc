#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <iostream>
#include <string>

using namespace std;
using namespace Poco::JSON;

string GetValue(Object::Ptr aoJsonObject, const char *aszKey) {
  Poco::Dynamic::Var loVariable;
  string lsReturn;
  string lsKey(aszKey);

  // Get the member Variable
  //
  loVariable = aoJsonObject->get(lsKey);

  // Get the Value from the Variable
  //
  lsReturn = loVariable.convert<std::string>();

  return lsReturn;
}

int main(int argc, char *argv[]) {
  string lsJson;
  Parser loParser;

  lsJson =
      "{\"TransactionCode\":\"000000\",\"FileRecordSequenceNumber\":\"111111\","
      "\"TcrSequenceNumber\":\"222222\",\"TransactionRouteIndicator\":"
      "\"ABCDE\",\"MerchantEstablishmentNumber\":\"00000000000\","
      "\"MerchantName\":\"BBBBBBBBB\",\"MerchantCity\":\"CCCCCCCC\"}";

  cout << lsJson << endl;

  // Parse the JSON and get the Results
  //
  Poco::Dynamic::Var loParsedJson = loParser.parse(lsJson);
  Poco::Dynamic::Var loParsedJsonResult = loParser.result();

  // Get the JSON Object
  //
  Object::Ptr loJsonObject = loParsedJsonResult.extract<Object::Ptr>();

  // Get the values for the member variables
  //
  //
  cout << "TransactionCode             "
       << GetValue(loJsonObject, "TransactionCode") << endl;
  cout << "FileRecordSequenceNumber    "
       << GetValue(loJsonObject, "FileRecordSequenceNumber") << endl;
  cout << "TcrSequenceNumber           "
       << GetValue(loJsonObject, "TcrSequenceNumber") << endl;
  cout << "TransactionRouteIndicator   "
       << GetValue(loJsonObject, "TransactionRouteIndicator") << endl;
  cout << "MerchantEstablishmentNumber "
       << GetValue(loJsonObject, "MerchantEstablishmentNumber") << endl;
  cout << "MerchantName                "
       << GetValue(loJsonObject, "MerchantName") << endl;
  cout << "MerchantCity                "
       << GetValue(loJsonObject, "MerchantCity") << endl;

  return 0;
}