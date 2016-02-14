
#define CONFINE( A, B, C )  ( ((A) < (B)) ? (B) : ( ((A) > (C)) ? (C) : (A) ) )

class PID
{
	double last_error;
	double integrated_error;
	double gain_limit;
	double target;

	double pT, iT, dT;
	double Kp, Ki, Kd;
	double K;

	double sweep;

	public:

	PID( double vtarget, double vK = 1.0, double vKp = 1.0, double vKi = 1.0, double vKd = 1.0 )
		: target(vtarget), 
		K(vK), Kp(vKp), Ki(vKi), Kd(vKd), 
		pT(0.0), iT(0.0), dT(0.0), 
		last_error(0.0), integrated_error(0.0),
		sweep(10000000.0)
	{
		
	}

	void set_target( double vtarget )
	{
		target = vtarget;
	}

	void set_sweep( double vsweep )
	{
		sweep = vsweep;
	}

	void set_gain_limit( double vgain_limit )
	{
		gain_limit = vgain_limit;
	}

	void set_correction_factors( double vK, double vKp, double vKi, double vKd )
	{
		K  = vK;
	        Kp = vKp;
		Ki = vKi; 
		Kd = vKd;
	}

	double update( double input )
	{
		double error = target - input;

		pT = Kp * error;
		integrated_error += error;
		iT = Ki * CONFINE( integrated_error, -gain_limit, gain_limit );
		dT = Kd * ( error - last_error );
		return -CONFINE( K * (pT + iT + dT), -sweep, sweep );
	}

	double pTerm() { return pT; }
	double iTerm() { return iT; }
	double dTerm() { return dT; }

};


