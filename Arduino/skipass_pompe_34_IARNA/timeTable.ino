
/*
   boiler priority:

  P_CORP_A      32  // boiler priroity
  P_CORP_B      33  // boiler priroity
  P_CORP_C      34  // boiler priroity
  P_CASUTA      35  // boiler priroity
  P_PARDOSEA    36  // boiler priroity
  P_PISCINA     37  // boiler priroity
  P_SCHIURI     38  // boiler priroity
  P_USCATOR     39  // boiler priroity
*/

void timeTable()
{
  static bool firstNotify = true;

  if (/*year() > 2018 && */!priorityModeBoiler) {
    switch (hour()) {

      case  0:
        digitalWrite(sp1Relay, RELAY_OFF);
        digitalWrite(sp2Relay, RELAY_ON);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_OFF);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_OFF);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_ON);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case  1:
        digitalWrite(sp1Relay, RELAY_OFF);
        digitalWrite(sp2Relay, RELAY_ON);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_OFF);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_OFF);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_OFF);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_OFF);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case  2:
        digitalWrite(sp1Relay, RELAY_OFF);
        digitalWrite(sp2Relay, RELAY_ON);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_OFF);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_OFF);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_OFF);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_ON);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case  3:
        digitalWrite(sp1Relay, RELAY_OFF);
        digitalWrite(sp2Relay, RELAY_ON);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_OFF);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_OFF);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_OFF);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_OFF);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case  4:
        digitalWrite(sp1Relay, RELAY_OFF);
        digitalWrite(sp2Relay, RELAY_ON);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_OFF);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_OFF);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_ON);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case  5:
        digitalWrite(sp1Relay, RELAY_OFF);
        digitalWrite(sp2Relay, RELAY_ON);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_OFF);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_OFF);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_OFF);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_OFF);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case  6:
        digitalWrite(sp1Relay, RELAY_OFF);
        digitalWrite(sp2Relay, RELAY_ON);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_OFF);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_OFF);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_OFF);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_ON);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case  7:
        digitalWrite(sp1Relay, RELAY_OFF);
        digitalWrite(sp2Relay, RELAY_ON);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_OFF);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_OFF);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_ON);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case  8:
        digitalWrite(sp1Relay, RELAY_OFF);
        digitalWrite(sp2Relay, RELAY_ON);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_OFF);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_OFF);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_OFF);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_OFF);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case  9:
        digitalWrite(sp1Relay, RELAY_OFF);
        digitalWrite(sp2Relay, RELAY_ON);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_OFF);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_OFF);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_ON);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 10:
        digitalWrite(sp1Relay, RELAY_ON);
        digitalWrite(sp2Relay, RELAY_OFF);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_OFF);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_OFF);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = true;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_ON);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_OFF);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 11:
        digitalWrite(sp1Relay, RELAY_ON);
        digitalWrite(sp2Relay, RELAY_OFF);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_OFF);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_OFF);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_OFF);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_OFF);
        if (modePiscina  == 2) poolEnabled = true;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_ON);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_OFF);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 12:
        digitalWrite(sp1Relay, RELAY_ON);
        digitalWrite(sp2Relay, RELAY_OFF);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_OFF);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_OFF);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_OFF);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_OFF);
        if (modePiscina  == 2) poolEnabled = true;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_ON);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_OFF);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 13:
        digitalWrite(sp1Relay, RELAY_ON);
        digitalWrite(sp2Relay, RELAY_OFF);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_OFF);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_OFF);
        if (modePiscina  == 2) poolEnabled = true;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_ON);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 14:
        digitalWrite(sp1Relay, RELAY_ON);
        digitalWrite(sp2Relay, RELAY_OFF);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2 && minute() >= 20) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2)                   digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2)                   digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2 && minute() >= 10) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2)                   digitalWrite(P_CASUTA,   RELAY_OFF);
        if (modePardosea == 2)                   digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2)                   digitalWrite(P_SCHIURI,  RELAY_ON);
        if (modeCentEl   == 2 && minute() <  30) digitalWrite(P_CENT_EL,  RELAY_ON);
        if (modeCentEl   == 2 && minute() >= 30) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 15:
        digitalWrite(sp1Relay, RELAY_ON);
        digitalWrite(sp2Relay, RELAY_OFF);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_ON);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_OFF);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 16:
        digitalWrite(sp1Relay, RELAY_ON);
        digitalWrite(sp2Relay, RELAY_OFF);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_OFF);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_ON);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 17:
        digitalWrite(sp1Relay, RELAY_ON);
        digitalWrite(sp2Relay, RELAY_OFF);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_OFF);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_OFF);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 18:
        digitalWrite(sp1Relay, RELAY_ON);
        digitalWrite(sp2Relay, RELAY_OFF);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2 && minute() >= 20) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2)                   digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2)                   digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2 && minute() >= 10) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2)                   digitalWrite(P_CASUTA,   RELAY_OFF);
        if (modePardosea == 2)                   digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2)                   digitalWrite(P_SCHIURI,  RELAY_OFF);
        if (modeCentEl   == 2 && minute() <  30) digitalWrite(P_CENT_EL,  RELAY_ON);
        if (modeCentEl   == 2 && minute() >= 30) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 19:
        digitalWrite(sp1Relay, RELAY_ON);
        digitalWrite(sp2Relay, RELAY_OFF);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_ON);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 20:
        digitalWrite(sp1Relay, RELAY_ON);
        digitalWrite(sp2Relay, RELAY_OFF);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 21:
        digitalWrite(sp1Relay, RELAY_ON);
        digitalWrite(sp2Relay, RELAY_OFF);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_ON);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 22:
        digitalWrite(sp1Relay, RELAY_OFF);
        digitalWrite(sp2Relay, RELAY_ON);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_ON);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_OFF);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_OFF);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      case 23:
        digitalWrite(sp1Relay, RELAY_OFF);
        digitalWrite(sp2Relay, RELAY_ON);
        digitalWrite(sp3Relay, RELAY_OFF);

        if (modeCorpA    == 2) digitalWrite(P_CORP_A,   RELAY_ON);
        if (modeCorpB    == 2) digitalWrite(P_CORP_B,   RELAY_ON);
        if (modeCamereB  == 2) digitalWrite(P_CAMERE_B, RELAY_ON);   // camere B
        if (modeCorpC    == 2) digitalWrite(P_CORP_C,   RELAY_ON);
        if (modePiscina  == 2) poolEnabled = false;
        if (modeCasuta   == 2) digitalWrite(P_CASUTA,   RELAY_OFF);
        if (modePardosea == 2) digitalWrite(P_PARDOSEA, RELAY_ON);
        if (modeSchiuri  == 2) digitalWrite(P_SCHIURI,  RELAY_OFF);
        if (modeCentEl   == 2) digitalWrite(P_CENT_EL,  RELAY_OFF);
        break;

      default:
        // if nothing else matches, do the default
        break;
    }
  }
  else if (firstNotify) {
    firstNotify = false;
    Blynk.notify(UNIT_NAME ": RTC error:" + getTime());

    terminal.println(getTime() + UNIT_NAME + ": RTC error!");
    terminal.flush();

    rtc.begin();
  }

  if (!digitalRead(sp1Relay) && !digitalRead(sp2Relay) && !digitalRead(sp3Relay)) {
    Blynk.virtualWrite(V_SP, "SP ERROR");  // for SP debug

    terminal.println(getTime() + UNIT_NAME + ": SP ERROR!");
    terminal.flush();
  }
  else if (!digitalRead(sp1Relay)) Blynk.virtualWrite(V_SP, "SP1");
  else if (!digitalRead(sp2Relay)) Blynk.virtualWrite(V_SP, "SP2");
  else if (!digitalRead(sp3Relay)) Blynk.virtualWrite(V_SP, "SP3");
}
