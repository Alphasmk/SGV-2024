﻿#include "stdafx.h"

#include "MFST.h"
#include "Error.h"

#include <fstream>
#include <iomanip>

using namespace std;
int FST_TRACE_n = -1;
char rbuf[205], sbuf[205], lbuf[1024];
namespace MFST
{
	Rl getrul(wchar_t rulefile[])
	{
		Rl rl;
		wcscpy_s(rl.rulefile, rulefile);
		ofstream* FILE = new ofstream;
		(*FILE).open(rulefile);
		if (!(*FILE).is_open())
			ERROR_THROW(107);
		rl.stream = FILE;
		return rl;
	}
	void WriteData(Rl rl)
	{
		char Date[50];
		struct tm* date;
		const time_t nowtime = time(NULL);
		date = localtime(&nowtime);
		strftime(Date, 50, "%d.%m.%Y %H:%M:%S, %A", date);
		*rl.stream << "----Протокол rl----" << endl;
		*rl.stream << "Время создания протокола: " << Date << endl;
	}
	MfstState::MfstState()
	{
		lenta_position = 0;
		nrule = -1;
		nrulechain = -1;
	}
	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrulechain)
	{
		lenta_position = pposition;
		st = pst;
		nrulechain = pnrulechain;
	}
	MfstState::MfstState(short pposition, MFSTSTSTACK pst, short pnrule, short pnrulechain)
	{
		lenta_position = pposition;
		st = pst;
		nrule = pnrule;
		nrulechain = pnrulechain;
	}
	Mfst::MfstDiagnosis::MfstDiagnosis()
	{
		lenta_position = -1;
		rc_step = SURPRISE;
		nrule = -1;
		nrule_chain = -1;
	}
	Mfst::MfstDiagnosis::MfstDiagnosis(short plenta_position, RC_STEP prc_step, short pnrule, short pnrule_chain)
	{
		lenta_position = plenta_position;
		rc_step = prc_step;
		nrule = pnrule;
		nrule_chain = pnrule_chain;
	}
	Mfst::Mfst()
	{
		lenta = 0;
		lenta_size = lenta_position = 0;
	}

	Mfst::Mfst(LT::LexTable plex, GRB::Greibach pgrebach, Log::LOG log)
	{
		grebach = pgrebach;
		lexTable = plex;
		lenta = new short[lenta_size = lexTable.size];
		for (int k = 0; k < lenta_size; k++) {
			lenta[k] = TS(lexTable.table[k].lexema);
		}
		lenta_position = 0;
		st.push(grebach.stbottomT);
		st.push(grebach.startN);
		nrulechain = -1;
	};

	Mfst::Mfst(LT::LexTable plex, GRB::Greibach pgrebach, MFST::Rl rl)
	{
		this->rl = rl;
		grebach = pgrebach;
		lexTable = plex;
		lenta = new short[lenta_size = lexTable.size];
		for (int i = 0; i < lenta_size; i++)
			lenta[i] = TS(lexTable.table[i].lexema);
		lenta_position = 0;
		st.push(grebach.stbottomT);
		st.push(grebach.startN);
		nrulechain = -1;
	}
	Mfst::RC_STEP Mfst::step(Log::LOG log)
	{
		RC_STEP rc = SURPRISE;
		if (lenta_position < lenta_size)
		{
			if (ISNS(st.top()))
			{
				GRB::Rule rule;
				if ((nrule = GRB::getGreibach().getRule(st.top(), rule)) >= 0)
				{
					GRB::Rule::Chain chain;
					if ((nrulechain = rule.getNextChain(lenta[lenta_position], chain, nrulechain + 1)) >= 0)
					{
						MFST_TRACE1(*log.stream);
						savestate(log);
						st.pop();
						push_chain(chain);
						rc = NS_OK;
						MFST_TRACE2(*log.stream);
					}
					else
					{
						MFST_TRACE4("TNS_NORULECHAIN/NS_NORULE", *log.stream)
							savediagnosis(NS_NORULECHAIN);
						rc = reststate(log) ? NS_NORULECHAIN : NS_NORULE;
					}
				}
				else
					rc = NS_ERROR;
			}
			else if ((st.top() == lenta[lenta_position]))
			{
				lenta_position++;
				st.pop();
				nrulechain = -1;
				rc = TS_OK;
				MFST_TRACE3(rl);
			}
			else
			{
				MFST_TRACE4("TS_NOK/NS_NORULECHAIN", *log.stream)
					rc = reststate(log) ? TS_NOK : NS_NORULECHAIN;
			}
		}
		else
		{
			rc = LENTA_END;
			MFST_TRACE4("LENTA_END", *log.stream)
		}
		return rc;
	}

	bool Mfst::push_chain(GRB::Rule::Chain chain)
	{
		for (int i = chain.size - 1; i >= 0; i--)
			st.push(chain.nt[i]);
		return true;
	}
	bool Mfst::savestate(Log::LOG log)
	{
		storestate.push(MfstState(lenta_position, st, nrule, nrulechain));
		*log.stream << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << "SAVESTATE:" << storestate.size() << endl;;
		return true;
	}
	bool Mfst::reststate(Log::LOG log)
	{
		bool rc = false;
		MfstState state;
		if (rc = (storestate.size() > 0))
		{
			state = storestate.top();
			lenta_position = state.lenta_position;
			st = state.st;
			nrule = state.nrule;
			nrulechain = state.nrulechain;
			storestate.pop();
			MFST_TRACE5("RESSTATE", *log.stream)
				MFST_TRACE2(*log.stream);
		}
		return rc;
	}
	bool Mfst::savediagnosis(RC_STEP prc_step)
	{
		bool rc = false;
		short k = 0;
		while (k < MFST_DIAGN_NUMBER && lenta_position <= diagnosis[k].lenta_position)
			k++;
		if (rc = (k < MFST_DIAGN_NUMBER))
		{
			diagnosis[k] = MfstDiagnosis(lenta_position, prc_step, nrule, nrulechain);
			for (short j = k + 1; j < MFST_DIAGN_NUMBER; j++)
				diagnosis[j].lenta_position = -1;
		}
		return rc;
	}
	bool Mfst::start(Log::LOG log)
	{
		bool rc = false;
		RC_STEP rc_step = SURPRISE;
		char buf[MFST_DIAGN_MAXSIZE];
		rc_step = step(log);
		while (rc_step == NS_OK || rc_step == NS_NORULECHAIN || rc_step == TS_OK || rc_step == TS_NOK)
			rc_step = step(log);
		switch (rc_step)
		{
		case NS_NORULE:
			MFST_TRACE4("-------> NS_NORULE", *log.stream);
			*log.stream << "--------------------------------------------------------------" << endl;
			*log.stream << getDiagnosis(0, buf, log) << endl;
			*log.stream << getDiagnosis(1, buf, log) << endl;
			*log.stream << getDiagnosis(2, buf, log) << endl;
			break;
		case NS_NORULECHAIN:
			MFST_TRACE4("------> NS_NORULECHAIN", *log.stream)
				break;
		case NS_ERROR:
			MFST_TRACE4("------> NS_ERROR", *log.stream)
				break;
		case LENTA_END:
			MFST_TRACE4("-------> NS_LENTA_END", *log.stream)
				*log.stream << "--------------------------------------------------------------" << endl;
			*log.stream << setw(4) << left << "Всего символов " << lenta_size << ", Синтаксический анализ выполнен без ошибок" << endl;
			rc = true;
			break;
		case SURPRISE:
			MFST_TRACE4("------> SURPRISE", rl)
				break;
		}
		return rc;
	}
	char* Mfst::getCSt(char* buf)
	{
		for (int i = (signed)st.size() - 1; i >= 0; --i)
		{
			short p = st._Get_container()[i];
			buf[st.size() - 1 - i] = GRB::Rule::Chain::alphabet_to_char(p);
		}
		buf[st.size()] = 0x00;
		return buf;
	}
	char* Mfst::getCLenta(char* buf, short pos, short n)
	{
		short i, k = (pos + n < lenta_size) ? pos + n : lenta_size;
		for (i = pos; i < k; i++)
			buf[i - pos] = GRB::Rule::Chain::alphabet_to_char(lenta[i]);
		buf[i - pos] = 0x00;
		return buf;
	}
	char* Mfst::getDiagnosis(short n, char* buf, Log::LOG log)
	{
		char* rc = { 0 };
		int errid = 0;
		int lpos = -1;
		if (n < MFST_DIAGN_NUMBER && (lpos = diagnosis[n].lenta_position) >= 0)
		{
			errid = grebach.getRule(diagnosis[n].nrule).iderror;
			Error::ERRORS err = Error::geterrorin(errid, 0, 0);
			ERROR_THROW(err.id, lexTable.table[lpos].sn, lexTable.table[lpos].indxTI);
			rc = buf;
		}
		return rc;
	}
	void Mfst::printrules(Log::LOG log)
	{
		MfstState state;
		GRB::Rule rule;
		for (unsigned short i = 0; i < storestate.size(); i++)
		{
			state = storestate._Get_container()[i];
			rule = grebach.getRule(state.nrule);
			MFST_TRACE7(*log.stream);
		}
	}
	bool Mfst::savededucation()
	{
		MfstState state;
		GRB::Rule rule;
		deducation.nrules = new short[deducation.size = storestate.size()];
		deducation.nrulechains = new short[deducation.size];
		for (unsigned short i = 0; i < storestate.size(); i++)
		{
			state = storestate._Get_container()[i];
			deducation.nrules[i] = state.nrule;
			deducation.nrulechains[i] = state.nrulechain;
		}
		return true;
	}
}