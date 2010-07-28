/*
 * effectsunitsslot.h
 *
 *  Created on: Jul 14, 2010
 *      Author: bruno
 */

#ifndef EFFECTSUNITSSLOT_H_
#define EFFECTSUNITSSLOT_H_

#include "effectsunits/effectsunitscontroller.h"
#include "effectsunitswidget.h"
#include <QSignalMapper>

class EffectsUnitsSlot : public QWidget {

	Q_OBJECT

public:
	EffectsUnitsSlot(QWidget * parent, EffectsUnitsController * m_pController, QDomNode node);
	virtual ~EffectsUnitsSlot();

	int getNextID();

public slots:
	void slotDeckUpdated(int i);

private:
	QList<EffectsUnitsWidget *> * m_pEffectsUnitsWidgets;

	static int NextID;
	int m_SlotID;
	QSignalMapper * m_pSignalMapper;
	QList<WPushButton*> m_DeckButtons;
};

#endif /* EFFECTSUNITSSLOT_H_ */
