
typedef enum
{
	AXIS_ERROR = -1,
	AXIS_NOREF = 0,
	AXIS_READY,
	AXIS_MOVING_LEFT,
	AXIS_MOVING_RIGHT,
	AXIS_MOVING_REF,
	AXIS_MOVING_S2X,
	AXIS_TIMEOUT_MOVEREF,
	AXIS_TIMEOUT_MOVELEFT,
	AXIS_TIMEOUT_MOVERIGHT
} TxtAxis_status_t;

uint8_t chM;
TxtAxis_status_t status;

void moveRef()
{
        // need to find what I need from this

        if (chM < 8) // chM is 0 and 1
        {
                pT->pTArea->ftX1out.distance[chM] = 0;
                pT->pTArea->ftX1out.motor_ex_cmd_id[chM]++;
        }
        else
        {
                (pT->pTArea+1)->ftX1out.distance[chM-8] = 0;
                (pT->pTArea+1)->ftX1out.motor_ex_cmd_id[chM-8]++;
        }

        setMotorLeft();
        setStatus(AXIS_MOVING_REF);

        auto start = std::chrono::system_clock::now();
        //while (true)
        //{
        //      //check switch ref
        //      //if (isSwitchPressed(chS1)) // switch is pressed at the beginning, so, I need to run those 2 functions
        //      //{
        //              setMotorOff();
        //              break;
        //      //}

        //      std::this_thread::sleep_for(std::chrono::milliseconds(CYCLE_MS_AXIS)); // give time to move the motor
        //}
        setMotorOff(); // as the loop was called just 1 time and it breaks at the beginning, so, I just need to call the setMotorOff() once.

        if (status == AXIS_MOVING_REF)
        {
                pos = 0;
                setStatus(AXIS_READY);
        }
}


void setStatus(TxtAxis_status_t st) {
	status=st;
	std::string sst = toString(status);
}

void TxtAxis::setMotorOff()
{
	if (chM < 8)
	{
		//assert(pT->pTArea);
		pT->pTArea->ftX1out.duty[chM*2] = 0;
		pT->pTArea->ftX1out.duty[chM*2+1] = 0;
	}
	else
	{
		//assert(pT->pTArea+1);
		(pT->pTArea+1)->ftX1out.duty[(chM-8)*2] = 0;
		(pT->pTArea+1)->ftX1out.duty[(chM-8)*2+1] = 0;
	}
}
