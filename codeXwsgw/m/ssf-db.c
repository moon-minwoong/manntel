#include <ssf-db.h>
#include <mdbc.h>
#include <time.h>
#include <ICodeX.h>

#define STATUS_0      "OFF"
#define STATUS_1      "XM_IDLE"
#define STATUS_2      "ON"

const int8_t SSF_TABLE[][4][32] =
{
  {
    "Knit_Weaving_Machine1",
    "Knit_Weaving_Machine2",
    "Knit_Weaving_Machine3",
    "Knit_Weaving_Machine4"
  },
  {
    "Knit_postprocessing",
  },
  {
    "Cutting_machine",
  },
  {
    "Vision_UL_Inspection",
  },
  {
    "Transfer_robot",
  },
  {
    "3D_Print",
  },
  {
    "UL_order_warehouse",
  },
  // 7
  {
    "Nosewpress",
  },
  {
    "AGV_UL_Order_warehouse",
  },
  ///9
  {
    "UL_subsidiary_warehouse",
  },
  {
    "Input_conveyorbelt",
  },
  {
    "Return_conveyorbelt",
  },
  // 12
  {
    "AirGun_Spray1",
    "AirGun_Spray2",
  },
  //13
  {
    "1_stitch_machine",
  },
  {
    "2_stitch_machine",
  },
  {
    "Zigzag_sewing", 
  },
  {
    "Hammer_machine",
  },
  {
    "Punching_machine",
  },
  //18
  {
    "BackcounterMolding",
  },
  //19
  {
    "Gathering_Sewing_Machine",
  },
  {
    "Strobe_Sewing",
  },
  // 21
  {
    "Multi_Color_Sewing_Machine",
  },
  {
    "Vision_Sewing_inspection",
  },
  {
    "RFID_Basket",
  },



  #if 0
  {
    "CAM_DATA",
  },
  {
    "MACHINE",
  },
  {
    "MATERIAL",
  },
  {
    "Machine_Parameter",
    "Machine_Parameter_Input",
  },
  {
    "PARTS_IMD",
  },
  {
    "PROCESS",
  },
  {
    "SAMPLE",
  },
  #endif

};


#define MAX_KD_DeviceInfo              33
typedef struct
{
  uint8_t id;
  int8_t did[8];
  int8_t model[16];
  int8_t wfactor[6][32];
  int8_t rfactor[6][8];
}KD_DeviceInfo;


int32_t fxMakeQuery(uint8_t* p, uint8_t* tag, uint8_t* v, int8_t* query)
{
  int32_t e = 0;
  time_t t = time(0);

  sprintf(query,
          "update Machine_Parameter_Out "
          "set "
          "status_log = '%s' "
          "date_time = '%d' "
          "where machine_code = 'UL%02d' "
          "and parameter_code = '%s'",
          v, t, *(p+1), tag);

  return e;
}

int32_t getDevID(uint8_t id, int8_t* did)
{
  if (id == 0x0B) sprintf(did, "UL01");
  else if (id == 0x0C) sprintf(did, "UL02");
  else if (id == 0x0D) sprintf(did, "UL03");
  else if (id == 0x0E) sprintf(did, "UL04");
  else if (id == 0x15) sprintf(did, "UL05");
  else if (id == 0x1F) sprintf(did, "UL06");
  else if (id == 0x29) sprintf(did, "UL07");
  else if (id == 0x33) sprintf(did, "UL08");
  else if (id == 0x3D) sprintf(did, "UL09");
  else if (id == 0x47) sprintf(did, "UL10");

  else if (id == 0x51) sprintf(did, "UL11");
  else if (id == 0x52) sprintf(did, "UL12");
  else if (id == 0x53) sprintf(did, "UL13");
  else if (id == 0x54) sprintf(did, "UL14");

  else if (id == 0x5B) sprintf(did, "UL15");
  else if (id == 0x65) sprintf(did, "UL16");
  else if (id == 0x6F) sprintf(did, "UL17");
  else if (id == 0x70) sprintf(did, "UL18");

  else if (id == 0x79) sprintf(did, "UL19");
  else if (id == 0x7A) sprintf(did, "UL20");

  else if (id == 0x83) sprintf(did, "UL21");
  else if (id == 0x8D) sprintf(did, "UL22");
  else if (id == 0x8E) sprintf(did, "UL23");
  else if (id == 0x97) sprintf(did, "UL24");
  else if (id == 0x98) sprintf(did, "UL25");
  else if (id == 0xA1) sprintf(did, "UL26");
  else if (id == 0xA2) sprintf(did, "UL27");

  else if (id == 0xAB) sprintf(did, "UL28");
  else if (id == 0xB5) sprintf(did, "UL29");
  else if (id == 0xBF) sprintf(did, "UL30");
  else if (id == 0xC9) sprintf(did, "UL31");
  else if (id == 0xD3) sprintf(did, "UL32");
  else if (id == 0xDD) sprintf(did, "UL33");
  return 0;
}

KD_DeviceInfo gdinfo[] =  {
  {0x0B, "UL01", "KCS-093",          { "ULW1", },  {"ULR1", "ULRLT1",  "ULRC1", "ULRD1", "ULRMV1"}},
  {0x0C, "UL02", "KCS-093",          { "ULW2", },  {"ULR2", "ULRLT2",  "ULRC2", "ULRD2", "ULRMV2"}},
  {0x0D, "UL03", "KCS-093",          { "ULW3", },  {"ULR3", "ULRLT3",  "ULRC3", "ULRD3", "ULRMV3"}},
  {0x0E, "UL04", "KCS-093",          { "ULW4", },  {"ULR4", "ULRLT4",  "ULRC4", "ULRD4", "ULRMV4"}},
  {0x15, "UL05", "DL-2015",          { "ULW5", },  {"ULR5", "ULRLT5",  "", "", ""}},
  {0x1F, "UL06", "",                 { "ULW6", },  {"ULR6", "ULRLT6",  "ULRC5", "", ""}},
  {0x29, "UL07", "IS2000C-23M(Set)", { "ULW7", },  {"ULR7", "ULRQ1",  "", "", ""}},
  {0x33, "UL08", "",                 { "ULW8", },  {"ULR8", "ULRMV5", "ULRA1", "", ""}},
  {0x3D, "UL09", "",                 { "ULW9", },  {"ULR9", "ULRD1", "ULRW1", "ULRI1", ""}},
  {0x47, "UL10", "",                 { "ULW10",},  {"ULRBC1", "", "", "", ""}},

  {0x51, "UL11", "    ",             { "ULW11",},  {"ULR10", "ULRLT7",  "ULRA2", "", ""}},
  {0x52, "UL12", "    ",             { "ULW12",},  {"ULR11", "ULRLT8",  "ULRA3", "", ""}},
  {0x53, "UL13", "    ",             { "ULW13",},  {"ULR12", "ULRLT9",  "ULRA4", "", ""}},
  {0x54, "UL14", "    ",             { "ULW14",},  {"ULR13", "ULRLT10", "ULRA5", "", ""}},

  {0x5B, "UL15", "    ",             { "ULW15",},  {"ULR14", "ULRMV6", "ULRA6", "", ""}},
  {0x65, "UL16", "    ",             { "ULW16",},  {"ULR15", "ULRP1","", "", ""}},
  {0x6F, "UL17", "    ",             { "ULW17",},  {"ULR16", "ULRLT11", "", "", ""}},
  {0x70, "UL18", "    ",             { "ULW18",},  {"ULR17", "ULRLT12", "", "", ""}},
  {0x79, "UL19", "    ",             { "ULW19",},  {"ULR18", "ULRLT13", "", "", ""}},
  {0x7A, "UL20", "    ",             { "ULW20",},  {"ULR19", "ULRLT14", "", "", ""}},
  {0x83, "UL21", "    ",             { "ULW21",},  {"ULR20", "ULRLT15", "", "", ""}},
  {0x8D, "UL22", "    ",             { "ULW22",},  {"ULR21", "ULRLT16", "", "", ""}},
  {0x8E, "UL23", "    ",             { "ULW23",},  {"ULR22", "ULRLT17", "", "", ""}},
  {0x97, "UL24", "    ",             { "ULW24",},  {"ULR23", "ULRLT18", "", "", ""}},
  {0x98, "UL25", "    ",             { "ULW25",},  {"ULR24", "ULRLT19", "", "", ""}},
  {0xA1, "UL26", "    ",             { "ULW26",},  {"ULR25", "ULRLT20", "ULRP2", "", ""}},
  {0xA2, "UL27", "    ",             { "ULW27",},  {"ULR26", "ULRLT21", "ULRP3", "", ""}},
  {0xAB, "UL28", "    ",             { "ULW28",},  {"ULR27", "ULRLT22", "", "", ""}},
  {0xB5, "UL29", "    ",             { "ULW29",},  {"ULR28", "ULRLT23", "", "", ""}},
  {0xBF, "UL30", "    ",             { "ULW30",},  {"ULR29", "ULRLT24", "", "", ""}},
  {0xC9, "UL31", "    ",             { "ULW31",},  {"ULR30", "ULRLT25", "ULRMV7", "", ""}},
  {0xD3, "UL32", "    ",             { "ULW32",},  {"ULR31", "ULRQ2", "", "", ""}},
  {0xDD, "UL33", "    ",             { "ULW33",},  {"ULRD1", "ULRC6", "ULRL1", "", ""}},
};


int32_t get_gdinfo_index(uint8_t id)
{
  int32_t e = -1;
  int32_t i = 0;
  for ( i=0 ; gdinfo[i].id != 0; i++ )
  {
    if ( gdinfo[i].id == id )
    {
      e = i;
      break;
    }
  }
  return e;
}


int32_t fxSSFDBWrite(void* h, int8_t* b, int32_t sz, uint8_t* query)
{
  int32_t  e = 0;
  int32_t  idx = 0;
  int32_t  i = 0;
  int32_t  gindex = 0;
  int8_t temp[32] = {0};
  int8_t qval[32][32] = {0};
  uint8_t tm[32] = {0};

  uint32_t tidx = 0;

  time_t t = time(0);

  //*(b + idx); idx++; //STX
  //*(b + idx); idx++; //CMD
  //*(b + idx); idx++; //LEN
  get_curr_time(tm, "-", "-", " ", ":", 0, 0, 0, 0, 0, 0, 0);
  //sprintf(qval[0], "%s", *(b + idx) == 0x00 ? STATUS_0 : *(b + idx) == 0x01 ? STATUS_1 : STATUS_2); idx++; //POWER ON/OFF
  //sprintf(qval[1], "%d", ((*(b + idx) & 0xFF) * 256) + (*(b + idx + 1) & 0xFF)); idx += 2;
  //sprintf(qval[2], "%d", ((*(b + idx) & 0xFF) * 256) + (*(b + idx + 1) & 0xFF)); idx += 2;
  //sprintf(qval[3], "%d", ((*(b + idx) & 0xFF) * 256) + (*(b + idx + 1) & 0xFF)); idx += 2;
  //*(b + idx); idx++; // 8
  //*(b + idx); idx++; // 9
  //*(b + idx); idx++; // 10
  //*(b + idx); idx++; //Check SUM
  //*(b + idx); idx++; //ETX


  //gindex = get_gdinfo_index( *(b+1) );
  //if ( gindex < 0 ) return 0;


  if ( *(b+3)==0x00 ) //off
  {
    sprintf(qval[0], "OFF");
  }
  else if ( *(b+3) == 0x01 ) // on
  {
    if ( *(b+17) == 0x00 ) //run
    {
      sprintf(qval[0], "RUN");
    }
    else if ( *(b+17) == 0x01 ) // idle
    {
      sprintf(qval[0], "XM_IDLE");
    }
    else if ( *(b+17) == 0x02 ) // off
    {
      sprintf(qval[0], "OFF");
    }
  }
  else
  {
    sprintf(qval[0], "OFF");
  }


  idx = 1;
  if ( (*(b+idx)==0x0B) || (*(b+idx)==0x0C) || (*(b+idx)==0x0D) || (*(b+idx)==0x0E) )
  {
    tidx = 0;
    sprintf(query,
      "insert into %s ( date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Defective, Normal, Motor_DIR ) "
      "values "
      "( '%s', '%d', '%s', '%s', '%s', '%s', '%d', '%d', '%s' )",
      SSF_TABLE[tidx][*(b+idx)-0x0B],
      tm, *(b+12), "", "", qval[0], (*(b+17))==0?"END":"BEGIN", ((*(b+15))<<8)+(*(b+16)), ((*(b+13))<<8)+(*(b+14)), *(b+11)==0?"CCW":"CW");

    e = mdbcQuery(h, 0, query, strlen(query));

  }
  else
  if ( *(b+idx) == 0x15 ) // 니트 후가공
  {
    tidx = 1;
    sprintf(query,
      "insert into %s ( date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Defective, Normal ) "
      "values "
      "( '%s', '%d', '%d', '%s', '%s', '%s', '%d', '%d' )",
      SSF_TABLE[tidx][0],
      tm, *(b+12), *(b+9), "", qval[0], (*(b+17))==0?"END":"BEGIN", ((*(b+15))<<8)+(*(b+16)), ((*(b+13))<<8)+(*(b+14)));
      //SSF_TABLE[1][0];
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( *(b+idx) == 0x1F )  // 재단기
  {
    tidx = 2;
    sprintf(query,
      "insert into %s ( date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Defective, Normal ) "
      "values "
      "( '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%d' )",
      SSF_TABLE[tidx][0],
      tm, "", "", "", qval[0], (*(b+17))==0?"END":"BEGIN", ((*(b+15))<<8)+(*(b+16)), ((*(b+13))<<8)+(*(b+14)));
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( *(b+idx) == 0x29 ) // 재단 검사 (비전검사)
  {
    tidx = 3;

    sprintf(query,
      "insert into %s ( date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Defective, Normal ) "
      "values "
      "( '%s', '%s', '%s', '%s', '%s', '%s', '%d', '%d' )",
      SSF_TABLE[tidx][0],
      tm, "", "", "", qval[0], (*(b+17))==0?"END":"BEGIN", ((*(b+15))<<8)+(*(b+16)), ((*(b+13))<<8)+(*(b+14)));
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( *(b+idx) == 0x29 ) // 투입 컨베이어
  {
    tidx = 10;
    sprintf(query,
      "insert into %s ( date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Defective, Normal, Motor_DIR ) "
      "values "
      "( '%s', '%d', '%s', '%s', '%s', '%s', '%d', '%d', '%s')",
      SSF_TABLE[tidx][0],
      tm, *(b+12), "", "", qval[0], (*(b+17))==0?"END":"BEGIN", ((*(b+15))<<8)+(*(b+16)), ((*(b+13))<<8)+(*(b+14)),  *(b+11)==0?"CCW":"CW");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( *(b+idx) == 0x3D ) // 이송로봇
  {
    tidx = 4;
    sprintf(query,
      "insert into %s ( date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Input, Subsidiary_Material, RFID_Attach, Order_UpperLeader, AGV, Return_Material ) "
      "values "
      "( '%s', '%d', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, *(b+12), "", "", qval[0], (*(b+17))==0?"END":"BEGIN", *(b+9)==0x01?"1":"0", *(b+9)==0x02?"1":"0", *(b+9)==0x03?"1":"0", *(b+9)==0x04?"1":"0", *(b+9)==0x05?"1":"0", *(b+9)==0x06?"1":"0");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( *(b+idx) == 0x47 ) // 적재창고
  {
    /// 녹색 바구니 9,10 ---> 부자재
    /// 빨간 바구니 11,12 --> UL order
    /// AGV       13,14 --> AGV 이송


    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Position1, Position2, Position3, Position4, Position5, Position6, Position7, Position8, Position9, Position10, Position11, Position12, Position13, Position14, Position15, Position16, Position17, Position18, Position19, Position20, Position21, Position22, Position23, Position24 ) "
      "values "
      "( '%s', '%d', '%s', '%s', '%s', '%s',     '%d', '%d', '%d', '%d', '%d', '%d',        '%d', '%d', '%d', '%d', '%d', '%d',       '%d', '%d', '%d', '%d', '%d', '%d',        '%d', '%d', '%d', '%d', '%d', '%d')",
      SSF_TABLE[9][0],
      tm, *(b+12), "", "", "", "",  *(b+9)==1?*(b+10):0,*(b+9)==2?*(b+10):0,*(b+9)==3?*(b+10):0,*(b+9)==4?*(b+10):0,*(b+9)==5?*(b+10):0,*(b+9)==6?*(b+10):0,*(b+9)==7?*(b+10):0,*(b+9)==8?*(b+10):0,*(b+9)==9?*(b+10):0,*(b+9)==10?*(b+10):0,*(b+9)==11?*(b+10):0,*(b+9)==12?*(b+10):0,*(b+9)==13?*(b+10):0,*(b+9)==14?*(b+10):0,*(b+9)==15?*(b+10):0,*(b+9)==16?*(b+10):0,*(b+9)==17?*(b+10):0,*(b+9)==18?*(b+10):0,*(b+9)==19?*(b+10):0,*(b+9)==20?*(b+10):0,*(b+9)==21?*(b+10):0,*(b+9)==22?*(b+10):0,*(b+9)==23?*(b+10):0,*(b+9)==24?*(b+10):0);
    e = mdbcQuery(h, 0, query, strlen(query));


    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Position1, Position2, Position3, Position4, Position5, Position6, Position7, Position8, Position9, Position10, Position11, Position12, Position13, Position14, Position15, Position16, Position17, Position18, Position19, Position20, Position21, Position22, Position23, Position24 ) "
      "values "
      "( '%s', '%d', '%s', '%s', '%s', '%s',     '%d', '%d', '%d', '%d', '%d', '%d',        '%d', '%d', '%d', '%d', '%d', '%d',       '%d', '%d', '%d', '%d', '%d', '%d',        '%d', '%d', '%d', '%d', '%d', '%d')",
      SSF_TABLE[8][0],
      tm, *(b+12), "", "", "", "",  *(b+11)==1?*(b+12):0,*(b+11)==2?*(b+12):0,*(b+11)==3?*(b+12):0,*(b+11)==4?*(b+12):0,*(b+11)==5?*(b+12):0,*(b+11)==6?*(b+12):0,*(b+11)==7?*(b+12):0,*(b+11)==8?*(b+12):0,*(b+11)==9?*(b+12):0,*(b+11)==10?*(b+12):0,*(b+11)==11?*(b+12):0,*(b+11)==12?*(b+12):0,*(b+11)==13?*(b+12):0,*(b+11)==14?*(b+12):0,*(b+11)==15?*(b+12):0,*(b+11)==16?*(b+12):0,*(b+11)==17?*(b+12):0,*(b+11)==18?*(b+12):0,*(b+11)==19?*(b+12):0,*(b+11)==20?*(b+12):0,*(b+11)==21?*(b+12):0,*(b+11)==22?*(b+12):0,*(b+11)==23?*(b+12):0,*(b+11)==24?*(b+12):0);
    e = mdbcQuery(h, 0, query, strlen(query));


    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Position1, Position2, Position3, Position4, Position5, Position6, Position7, Position8, Position9, Position10, Position11, Position12, Position13, Position14, Position15, Position16, Position17, Position18, Position19, Position20, Position21, Position22, Position23, Position24 ) "
      "values "
      "( '%s', '%d', '%s', '%s', '%s', '%s',     '%d', '%d', '%d', '%d', '%d', '%d',        '%d', '%d', '%d', '%d', '%d', '%d',       '%d', '%d', '%d', '%d', '%d', '%d',        '%d', '%d', '%d', '%d', '%d', '%d')",
      SSF_TABLE[6][0],
      tm, *(b+12), "", "", "", "",  *(b+13)==1?*(b+14):0,*(b+13)==2?*(b+14):0,*(b+13)==3?*(b+14):0,*(b+13)==4?*(b+14):0,*(b+13)==5?*(b+14):0,*(b+13)==6?*(b+14):0,*(b+13)==7?*(b+14):0,*(b+13)==8?*(b+14):0,*(b+13)==9?*(b+14):0,*(b+13)==10?*(b+14):0,*(b+13)==11?*(b+14):0,*(b+13)==12?*(b+14):0,*(b+13)==13?*(b+14):0,*(b+13)==14?*(b+14):0,*(b+13)==15?*(b+14):0,*(b+13)==16?*(b+14):0,*(b+13)==17?*(b+14):0,*(b+13)==18?*(b+14):0,*(b+13)==19?*(b+14):0,*(b+13)==20?*(b+14):0,*(b+13)==21?*(b+14):0,*(b+13)==22?*(b+14):0,*(b+13)==23?*(b+14):0,*(b+13)==24?*(b+14):0);
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( (*(b+idx)==0x51) || (*(b+idx)==0x52) || (*(b+idx)==0x53) || (*(b+idx)==0x54) ) // 갑피 3D 프린팅
  {
    tidx = 5;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Equipment_Time, Bed_temperature, Head_temperature, Head_speed, Defective, Normal, Start_time, Stop_time, Lead_time) "
      "values "
      "( '%s', '%s', '%s', '%s', '%s', '%s',        '%02d:%02d:%02d', '%d', '%d', '%d', '%d', '%d', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, "", "", "", qval[0],  (*(b+17))==0?"END":"BEGIN",      *(b+4), *(b+5), *(b+6),         *(b+7), *(b+9), ((*(b+11))<<8)+(*(b+12)), ((*(b+15))<<8)+(*(b+16)), ((*(b+13))<<8)+(*(b+14)), *(b+17)==1?tm:"", *(b+17)==0?tm:"", "");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( *(b+idx) == 0x5B ) // 배출 컨베이어
  {
    tidx = 11;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Motor_DIR) "
      "values "
      "( '%s', '%d', '%s', '%s', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, *(b+12), "", "", qval[0], (*(b+17))==0?"END":"BEGIN", *(b+11)==0?"CCW":"CW");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( *(b+idx) == 0x65 ) // 노소프레스
  {
    tidx = 7;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Defective, Normal, Start_time, Stop_time, Lead_time ) "
      "values "
      "( '%s', '%s', '%s', '%d', '%s', '%s', '%d', '%d', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, "", "", *(b+12), qval[0], (*(b+17))==0?"END":"BEGIN", ((*(b+15))<<8)+(*(b+16)), ((*(b+13))<<8)+(*(b+14)), *(b+17)==1?tm:"", *(b+17)==0?tm:"", "");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( (*(b+idx)==0x6F) || (*(b+idx)==0x70) ) // 에어건 스프레이
  {
    tidx = 12;
    
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Start_time, Stop_time, Lead_time ) "
      "values "
      "( '%s', '%s', '%s', '%d', '%s', '%s', '%s', '%s', '%s')",
      SSF_TABLE[tidx][*(b+idx)-0x6F],
      tm, "", "", *(b+12), qval[0], (*(b+17))==0?"END":"BEGIN", *(b+17)==1?tm:"", *(b+17)==0?tm:"", "");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( (*(b+idx)==0x79) || (*(b+idx)==0x7A) ) // 1본침 재봉기
  {
    tidx = 13;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Start_time, Stop_time, Lead_time ) "
      "values "
      "( '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, "", "", "", qval[0], (*(b+17))==0?"END":"BEGIN", *(b+17)==1?tm:"", *(b+17)==0?tm:"", "");
    e = mdbcQuery(h, 0, query, strlen(query));

  }
  else
  if ( (*(b+idx)==0x83)  ) // 2본침 재봉기
  {
    tidx = 14;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Start_time, Stop_time, Lead_time ) "
      "values "
      "( '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, "", "", "", qval[0], (*(b+17))==0?"END":"BEGIN", *(b+17)==1?tm:"", *(b+17)==0?tm:"", "");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( (*(b+idx)==0x8D) || (*(b+idx)==0x8E) ) // 지그재그
  {
    tidx = 15;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Start_time, Stop_time, Lead_time ) "
      "values "
      "( '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, "", "", "", qval[0], (*(b+17))==0?"END":"BEGIN", *(b+17)==1?tm:"", *(b+17)==0?tm:"", "");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( (*(b+idx)==0x97) || (*(b+idx)==0x98) ) // 헤머링
  {
    tidx = 16;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Start_time, Stop_time, Lead_time ) "
      "values "
      "( '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, "", "", "", qval[0], (*(b+17))==0?"END":"BEGIN", *(b+17)==1?tm:"", *(b+17)==0?tm:"", "");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( (*(b+idx)==0xA1) || (*(b+idx)==0xA2) ) // 펀칭
  {
    tidx = 17;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Start_time, Stop_time, Lead_time ) "
      "values "
      "( '%s', '%s', '%s', '%d', '%s', '%s', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, "", "", *(b+12), qval[0], (*(b+17))==0?"END":"BEGIN", *(b+17)==1?tm:"", *(b+17)==0?tm:"", "");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( (*(b+idx)==0xA8) ) // 백카운터 몰딩
  {
    tidx = 18;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Start_time, Stop_time, Lead_time ) "
      "values "
      "( '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, "", "", "", qval[0], (*(b+17))==0?"END":"BEGIN", *(b+17)==1?tm:"", *(b+17)==0?tm:"", "");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( (*(b+idx)==0xB5) ) // 게더링
  {
    tidx = 19;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Start_time, Stop_time, Lead_time ) "
      "values "
      "( '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, "", "", "", qval[0], (*(b+17))==0?"END":"BEGIN", *(b+17)==1?tm:"", *(b+17)==0?tm:"", "");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( (*(b+idx)==0xBF) ) // 스트로벨 재봉
  {
    tidx = 20;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Start_time, Stop_time, Lead_time ) "
      "values "
      "( '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, "", "", "", qval[0], (*(b+17))==0?"END":"BEGIN", *(b+17)==1?tm:"", *(b+17)==0?tm:"", "");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( (*(b+idx)==0xC9) ) // 멀티컬러 재봉
  {
    tidx = 21;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Defective, Normal, Color_number, UL_Design, Start_time, Stop_time, Lead_time ) "
      "values "
      "( '%s', '%s', '%s', '%s', '%s', '%s',      '%d', '%d', '%d', '%d', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, "", "", "", qval[0], (*(b+17))==0?"END":"BEGIN", ((*(b+15))<<8)+(*(b+16)), ((*(b+13))<<8)+(*(b+14)), *(b+7), ((*(b+8))<<8)+(*(b+9)), *(b+17)==1?tm:"", *(b+17)==0?tm:"", "");
    e = mdbcQuery(h, 0, query, strlen(query));
  }
  else
  if ( (*(b+idx)==0xD3) ) // 재봉검사
  {
    tidx = 22;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Defective, Normal, Start_time, Stop_time, Lead_time ) "
      "values "
      "( '%s', '%s', '%s', '%s', '%s', '%s',      '%d', '%d', '%s', '%s', '%s')",
      SSF_TABLE[tidx][0],
      tm, "", "", "", qval[0], (*(b+17))==0?"END":"BEGIN", ((*(b+15))<<8)+(*(b+16)), ((*(b+13))<<8)+(*(b+14)), *(b+17)==1?tm:"", *(b+17)==0?tm:"", "");
    e = mdbcQuery(h, 0, query, strlen(query));

  }
  else
  if ( (*(b+idx)==0xDD) ) // 갑피 RFID
  {
    tidx = 23;
    sprintf(query,
      "insert into %s (  date_time, RPM, temp, pressure, Power_on_off, Equipment_Lamp, Defective, Normal, Basket_position, Basket_data ) "
      "values "
      "( '%s', '%s', '%s', '%s', '%s', '%s',      '%d', '%d', '%d', '%d')",
      SSF_TABLE[tidx][0],
      tm, "", "", "", qval[0], (*(b+17))==0?"END":"BEGIN", ((*(b+15))<<8)+(*(b+16)), ((*(b+13))<<8)+(*(b+14)), *(b+12), ((*(b+8))<<8)+(*(b+9)));
    e = mdbcQuery(h, 0, query, strlen(query));

  }

  return e;
}

