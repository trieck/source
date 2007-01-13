

#Definitions 

OBJS1=main.oo Vehicle.oo Van.oo PersonalVehicle.oo FourWheelDriveVehicle.oo SUV.oo
OBJS2=main.o Vehicle.o Van.o PersonalVehicle.o FourWheelDriveVehicle.o SUV.o


#Dependency rules

drive1 : ${OBJS1}
	g++ ${OBJS1} -o drive1
main.oo : main.cpp SUV.hpp PersonalVehicle.hpp FourWheelDriveVehicle.hpp Van.hpp Vehicle.hpp
	g++ -c main.cpp -o main.oo
SUV.oo : SUV.cpp SUV.hpp PersonalVehicle.hpp FourWheelDriveVehicle.hpp Vehicle.hpp 
	g++ -c SUV.cpp -o SUV.oo
PersonalVehicle.oo : PersonalVehicle.cpp PersonalVehicle.hpp Vehicle.hpp 
	g++ -c PersonalVehicle.cpp -o PersonalVehicle.oo
FourWheelDriveVehicle.oo : FourWheelDriveVehicle.cpp FourWheelDriveVehicle.hpp Vehicle.hpp 
	g++ -c FourWheelDriveVehicle.cpp -o FourWheelDriveVehicle.oo 
Van.oo : Van.cpp Van.h Vehicle.hpp 
	g++ -c Van.cpp -o Van.oo
Vehicle.oo : Vehicle.cpp Vehicle.hpp
	g++ -c Vehicle.cpp -o Vehicle.oo

drive2 : ${OBJS2}
	cc ${OBJS2} -o drive2
main.o : main.c SUV.h PersonalVehicle.h FourWheelDriveVehicle.h Van.h Vehicle.h
	cc -c main.c 
SUV.o : SUV.c SUV.h PersonalVehicle.h FourWheelDriveVehicle.h Vehicle.h 
	cc -c SUV.c
PersonalVehicle.o : PersonalVehicle.c PersonalVehicle.h Vehicle.h 
	cc -c PersonalVehicle.c
FourWheelDriveVehicle.o : FourWheelDriveVehicle.c FourWheelDriveVehicle.h Vehicle.h 
	cc -c FourWheelDriveVehicle.c
Van.o : Van.cpp Van.h Vehicle.h 
	cc -c Van.c
Vehicle.o : Vehicle.c Vehicle.h
	cc -c Vehicle.c

clean: 
	rm -f ${OBJS1} ${OBJS2} drive1 drive2

all:	drive1 drive2

