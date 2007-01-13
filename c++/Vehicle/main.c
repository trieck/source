


			/* main.c */


#include <stdio.h> 
#include "Van.h" 
#include "SUV.h" 

main() { 

   build_vtbl_Vehicle(); 
   build_vtbl_Van(); 
   build_vtbl_PersonalVehicle(); 
   build_vtbl_PersonalVehicle(); 
   build_vtbl_PersonalVehicle_Vehicle(); 
   build_vtbl_FourWheelDriveVehicle(); 
   build_vtbl_FourWheelDriveVehicle_Vehicle(); 
   build_vtbl_SUV(); 
   build_vtbl_SUV_Vehicle(); 
   build_vtbl_SUV_FourWheelDriveVehicle(); 

   Van* van = Van_new_DefaultConstructor(); 
   SUV* suv = SUV_new_DefaultConstructor(); 
   SUV* suv2 = SUV_new_CopyConstructor(suv); 
   printf("%d\n", Vehicle_count()); 
   printf("%d %s %d\n", 
      Vehicle_id(&(van->vehicle)),
      Vehicle_make(&(van->vehicle)), 
      Van_number_seats(van)
   );
   printf("%d %d %d\n", 
      Vehicle_id(suv->pVehicle),
      PersonalVehicle_junk(&(suv->personalVehicle)), 
      FourWheelDriveVehicle_junk(&(suv->fourWheelDriveVehicle)) 
   );
   Vehicle* v = (Vehicle*) van; 
   Vehicle_drive(v); 
   Van_drive(van); 

   // virtually invoke vDrive and clone 

   void (*fp1)(Vehicle*); 
   fp1 = v->_vptr[0]; 
   (*fp1)(v); 

   void (*fp2)(Van*); 
   fp2 = van->_vptr[0]; 
   (*fp2)(van); 

   void (*fp3)(SUV*); 
   fp3 = suv->_vptr[0]; 
   (*fp3)(suv); 

   v = suv->pVehicle; 
   fp1 = v->_vptr[0]; 
   (*fp1)(v); 

   v = suv2->pVehicle; 
   fp1 = v->_vptr[0]; 
   (*fp1)(v); 

   Vehicle* (*fp4)(Vehicle*); 
   fp4 = v->_vptr[1]; 
   Vehicle* v2 = (*fp4)(v);   
   fp1 = v2->_vptr[0]; 
   (*fp1)(v2); 


} 


