#include "stdafx.h"

bool connecterFSX();
bool connecterHLA();


int     quit = 0;
HANDLE  hSimConnect = NULL;

static enum GROUP_ID {
    GROUP_1,
};

static enum INPUT_ID {
    INPUT_1,
};

static enum EVENT_ID{
    EVENT_SIM_START,
	EVENT_SIM_PAUSE,
    EVENT_1,
};

static enum DATA_DEFINE_ID {
    DEFINITION_POSITION,
	DEFINITION_ALTITUDE,
	DEFINITION_LATITUDE,
	DEFINITION_LONGITUDE,
	DEFINITION_VITESSE_LONGITUDINALE,
	DEFINITION_VITESSE_LATERALE,
	DEFINITION_VITESSE_VERTICALE,
};

static enum DATA_REQUEST_ID {
    REQUEST_1,
	REQUEST_ALTITUDE,
	REQUEST_LATITUDE,
	REQUEST_LONGITUDE,
	REQUEST_VITESSE_LONGITUDINALE,
	REQUEST_VITESSE_LATERALE,
	REQUEST_VITESSE_VERTICALE,
};

void CALLBACK MyDispatchProcSD(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext)
{
    HRESULT hr;
    
    switch(pData->dwID)
    {
        case SIMCONNECT_RECV_ID_EVENT:
        {
            SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)pData;

            switch(evt->uEventID)
            {
                case EVENT_SIM_START:
                    {
                        // Turn the ctrl-shift-u input event on now
                        hr = SimConnect_SetInputGroupState(hSimConnect, INPUT_1, SIMCONNECT_STATE_ON);
						printf("FSX : Simulation demarree\n");
						 break;
                    }

                case EVENT_1:
                    {
						printf("FSX : Ctrl-Shift-A presse\n");
                        SIMCONNECT_DATA_INITPOSITION Init;
                        Init.Altitude   = 35000.0;
                        Init.Latitude   = 0.0;
                        Init.Longitude  = 0.0;
                        Init.Pitch      =  0.0;
                        Init.Bank       = -1.0;
                        Init.Heading    = 0.0;
                        Init.OnGround   = 0;
                        Init.Airspeed    = 60;
                        //hr = SimConnect_SetDataOnSimObject(hSimConnect, DEFINITION_POSITION, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(Init), &Init );
						//hr = SimConnect_RequestDataOnSimObject(hSimConnect, REQUEST_ALTITUDE, DEFINITION_ALTITUDE, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);
						//hr = SimConnect_RequestDataOnSimObject(hSimConnect, REQUEST_LATITUDE, DEFINITION_LATITUDE, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);
						//hr = SimConnect_RequestDataOnSimObject(hSimConnect, REQUEST_LONGITUDE, DEFINITION_LONGITUDE, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);
						hr = SimConnect_RequestDataOnSimObject(hSimConnect, REQUEST_VITESSE_LONGITUDINALE, DEFINITION_VITESSE_LONGITUDINALE, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);
						//hr = SimConnect_RequestDataOnSimObject(hSimConnect, REQUEST_VITESSE_LATERALE, DEFINITION_VITESSE_LATERALE, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);
						//hr = SimConnect_RequestDataOnSimObject(hSimConnect, REQUEST_VITESSE_VERTICALE, DEFINITION_VITESSE_VERTICALE, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_ONCE);
						break;
                    }
                   

				case EVENT_SIM_PAUSE:
                    {
						if(evt->dwData==1) { 
							printf("FSX : Mise en pause\n");
						}
						else {
							printf("FSX : Sortie de pause\n");
						}
						break;
                    }

                default:
                    break;
            }
            break;
        }

		case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
		{
			SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*) pData;

			switch(pObjData->dwRequestID)
			{
				case REQUEST_ALTITUDE:
					{
						double *pS = (double*)&pObjData->dwData;
						printf("FSX : Altitude : %f\n",*pS);
						*pS = *pS +10.;
						SimConnect_SetDataOnSimObject(hSimConnect, DEFINITION_ALTITUDE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(*pS), pS);
						break;
					}

				case REQUEST_LATITUDE:
					{
						double *pS = (double*)&pObjData->dwData;
						printf("FSX : Latitude : %f\n",*pS);
						*pS = *pS +0.0000088147 /* 1m a l equateur */ * 100;
						SimConnect_SetDataOnSimObject(hSimConnect, DEFINITION_LATITUDE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(*pS), pS);
						break;
					}

				case REQUEST_LONGITUDE:
					{
						double *pS = (double*)&pObjData->dwData;
						printf("FSX : Longitude : %f\n",*pS);
						*pS = *pS +0.0000088147 /* 1m a l equateur */ * 100;
						SimConnect_SetDataOnSimObject(hSimConnect, DEFINITION_LONGITUDE, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(*pS), pS);
						break;
					}
			}
			break;
		}

        case SIMCONNECT_RECV_ID_QUIT:
        {
            quit = 1;
            break;
        }

        default:
			printf("FSX : Recu : %d\n",pData->dwID);
            break;
    }
}

void lancerModule()
{
	if(connecterFSX() && connecterHLA()){
		HRESULT hr;

        while( 0 == quit )
        {
            SimConnect_CallDispatch(hSimConnect, MyDispatchProcSD, NULL);
            Sleep(1);
        } 

        hr = SimConnect_Close(hSimConnect);
    }
}

bool connecterFSX() {

	// On se connecte ici a FSX via l'API SimConnect 
	
    if (SUCCEEDED(SimConnect_Open(&hSimConnect, "FSX SDSE", NULL, 0, 0, 0))){
		HRESULT hr;
        // Set up a data definition for positioning data
        hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_POSITION, "Initial Position", NULL, SIMCONNECT_DATATYPE_INITPOSITION);
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_ALTITUDE, "Plane Altitude", "feet");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_LATITUDE, "Plane Latitude", "degrees");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_LONGITUDE, "Plane Longitude", "degrees");

		// Request a simulation start event
        hr = SimConnect_SubscribeToSystemEvent(hSimConnect, EVENT_SIM_START, "SimStart");
		hr = SimConnect_SubscribeToSystemEvent(hSimConnect, EVENT_SIM_PAUSE, "Pause");

        // Create a custom event
        hr = SimConnect_MapClientEventToSimEvent(hSimConnect, EVENT_1, "My.CTRLSHIFTA");

        // Link the custom event to some keyboard keys, and turn the input event off
        hr = SimConnect_MapInputEventToClientEvent(hSimConnect, INPUT_1, "ctrl+shift+A", EVENT_1);
        hr = SimConnect_SetInputGroupState(hSimConnect, INPUT_1, SIMCONNECT_STATE_OFF);

        // Sign up for notifications for EVENT_1
        hr = SimConnect_AddClientEventToNotificationGroup(hSimConnect, GROUP_1, EVENT_1);

		printf("FSX : Connecte\n");
		return true;
	}
	else {
		printf("FSX : Erreur a la connexion\n");
		return false;
	}
}

bool connecterHLA() {
	printf("HLA : Connecte\n");
	return true;
}


int __cdecl _tmain(int argc, _TCHAR* argv[])
{
	printf("FSX SDSE Plugin...\n");
    lancerModule();


    return 0;
} 