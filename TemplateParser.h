#ifndef _TEMPLATE_PARSER_H_
#define _TEMPLATE_PARSER_H_
#include <iostream>
#include <vector>
#include <typeindex>
#include <unordered_map>
struct ComponentDataArray;

/*template <size_t N, typename... T>
struct Iterator {
	static void GetTypeSizes(std::vector<size_t> &vector) {
		vector.push_back(sizeof(std::tuple_element<N, std::tuple<T...>>::type));
		Iterator<N - 1, T...>::GetTypeSizes(vector);
	}
	static void CreateComponentTypeList(std::vector<std::string> &vector) {
		vector.push_back(typeid(std::tuple_element<N, std::tuple<T...>>::type).name());
		Iterator<N - 1, T...>::CreateComponentTypeList(vector);
	}
	static void print() {
		std::cout << typeid(std::tuple_element<N, std::tuple<T...>>::type).name() << " ";
		Iterator<N - 1, T...>::print();
	}
};

template<typename... T>
struct Iterator<0, T...> {
	static void GetTypeSizes(std::vector<size_t>& vector) {
		vector.push_back(sizeof(std::tuple_element<0, std::tuple<T...>>::type));
	}
	static void CreateComponentTypeList(std::vector<std::string>& vector) {
		vector.push_back(typeid(std::tuple_element<0, std::tuple<T...>>::type).name());
	}
	static void print() {
		std::cout << typeid(std::tuple_element<0, std::tuple<T...>>::type).name() << " ";
	}
};*/

/*template<typename T> void print(T t) {
	std::cout << typeid(t).name() << std::endl;
}

template<typename T0, typename... T> void print(T0 t0, T... t) {
	std::cout << typeid(t0).name() << std::endl;
	print(t...);
}*/

/*Recursive Parsing of Templates*/
namespace  TemplateParseParameter{
	template<typename Component> static void ComponentTypesToVector(std::vector<std::type_index>& vector, Component component) {
		vector.push_back(typeid(component));
	}

	template<typename Component, typename... Components> static void ComponentTypesToVector(std::vector<std::type_index>& vector, Component component, Components... components) {
		vector.push_back(typeid(component));
		ComponentTypesToVector(vector, components...);
	}

	template<typename Component> static void AddEntityToArchetype(ComponentDataArray* cda, Component component) {
		AddToComponentDataArray(cda, (void*)&component);
	}

	template<typename Component, typename... Components> static void  AddEntityToArchetype(ComponentDataArray* cda, Component component, Components... components) {
		AddToComponentDataArray(cda, (void*)&component);
		AddEntityToArchetype((cda + 1), components...);
	}
}

template<typename... Components> struct TemplateParseType;

template<typename Component, typename...Components> struct TemplateParseType<Component, Components...> {
	static void InitializeComponentDataArrays(ComponentDataArray* cda) {
		InitializeComponentDataArray(cda, 0, sizeof(Component));
		TemplateParseType<Components...>::InitializeComponentDataArrays((cda + 1));
	}

	static void InitializeComponentTypeRowIndexMap(std::unordered_map<std::type_index, unsigned int>& map) {
		map.insert(std::pair<std::type_index, unsigned int>(typeid(Component), map.size()));
		TemplateParseType<Components...>::InitializeComponentTypeRowIndexMap(map);
	}
};

template<> struct TemplateParseType<> {
	static void InitializeComponentDataArrays(ComponentDataArray* cda) {}
	static void InitializeComponentTypeRowIndexMap(std::unordered_map<std::type_index, unsigned int>& map) {}
};
#endif