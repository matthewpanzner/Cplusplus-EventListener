#ifndef MOOSE_EVENT_HPP
#define MOOSE_EVENT_HPP

#include "config.hpp"
#include <iostream>
#include <map>

//A generic event that uses a variant struct to hold arguments

struct Variant
{
	enum VariantType {UNINTIALIZED, DOUBLE, STRING, INTEGER, BOOLEAN}; //datatype id
	VariantType dataType = UNINTIALIZED;

	union{	
		double asDouble;
		char* asString;
		__int32 asInteger;
		bool asBoolean;
	};


};

class EXPORT Event
{
public:

	//Constructors
	Event() {}

	Event(char* eventName){
		//Initialize event with name
		SetEventName(eventName);
	}

	template<class T>
	Event(char* eventName, Variant::VariantType dataType, char* atrTitle, T value){
		SetEventName(eventName);
		switch (dataType){
		case Variant::DOUBLE:
			addArgAsFloat(atrTitle, value);
			break;

		case Variant::INTEGER:
			addArgAsInteger(atrTitle, value);
			break;
		case Variant::STRING:
			addArgAsString(atrTitle, value);
			break;
		case Variant::BOOLEAN:
			addArgAsBoolean(atrTitle, value);
			break;

		case Variant::UNINTIALIZED:
		default:
			ErrorArg(atrTitle, value);
			break;
		}
	}
	//Title manipulation

	inline char* GetEventName() { return this->args["event"].asString; }
	//Get the name of the event

	inline void SetEventName(char* eventName) { Variant var; var.asString = eventName; this->args["event"] = var; }
	//Set the name of the event



	//************************************************************
	// Set Args
	inline void addArgAsFloat(char* atrTitle, double value)
	//Add the event argument with title of atrTitle
	{
		Variant var;
		var.asDouble = value;
		var.dataType = var.DOUBLE;

		this->args[atrTitle] = var;
	}

	inline void addArgAsInteger(char* atrTitle, __int32 value)
	//Add the event argument with title of atrTitle
	{
		Variant var;
		var.asInteger = value;
		var.dataType = var.INTEGER;

		this->args[atrTitle] = var;
	}

	inline void addArgAsBoolean(char* atrTitle, bool value)
	//Add the event argument with title of atrTitle
	{
		Variant var;
		var.asBoolean = value;
		var.dataType = var.BOOLEAN;

		this->args[atrTitle] = var;
	}

	inline void addArgAsString(char* atrTitle, char* value)
		//Add event atrTitle with value 
	{
		Variant var;
		var.asString = value;
		var.dataType = var.STRING;

		this->args[atrTitle] = var;
	}

	//************************************************************
	// Get Args

	inline char* getArgAsString(char* atrTitle) {
		return this->args[atrTitle].asString;
	}
	inline _Uint32t getArgAsInteger(char* atrTitle) {
		return this->args[atrTitle].asInteger;
	}
	inline double getArgAsFloat(char* atrTitle) {
		return this->args[atrTitle].asDouble;
	}
	inline bool getArgAsBoolean(char* atrTitle) {
		return this->args[atrTitle].asBoolean;
	}

	template<class argType>
	inline argType getArg(char* atrTitle){
		switch (this->args[atrTitle].dataType){

		case Variant::DOUBLE:
			return this->args[atrTitle].asDouble;
			break;

		case Variant::INTEGER:
			return this->args[atrTitle].asInteger;
			break;
		case Variant::STRING:
			return this->args[atrTitle].asString;
			break;
		case Variant::BOOLEAN:
			return this->args[atrTitle].asBoolean;
			break;

		case Variant::UNINTIALIZED:
		default:
			std::cout << "Uninitialized event type, cannot use";
			break;
		}
	}
	


	//In the case you need the full mapping.
	//  Unsure if this is necessary yet
	inline std::map<char*, Variant> getAllArgs() const { return this->args; }

private:
	inline void ErrorArg(char* atrTitle, char* value){
		Variant var;
		var.asString = value;
		var.dataType = var.UNINTIALIZED;

		this->args[atrTitle] = var;
	}

	std::map<char*, Variant> args; //Stores all event arguments including its name
};

#endif