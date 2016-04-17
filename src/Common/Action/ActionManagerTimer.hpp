/*!
 * \file
 * \brief Définition de la classe ActionManager.
 */

#ifndef COMMON_ACTIONMANAGERTIMER_HPP_
#define COMMON_ACTIONMANAGERTIMER_HPP_

#include <list>
#include <string>

#include "../../Log/Logger.hpp"
#include "../../Log/LoggerFactory.hpp"
#include "../../Thread/Thread.hpp"
#include "../Utils/Chronometer.hpp"
#include "../Utils/PointerList.hpp"
#include "IAction.hpp"
#include "ITimerListener.hpp"


/*!
 * \brief Classe de gestion des actions du robot et des actions par timer
 */
class ActionManagerTimer: public utils::Thread
{
private:

	/*!
	 * \brief Retourne le \ref Logger associé à la classe \ref ActionManagerTimer.
	 */
	static inline const logs::Logger & logger()
	{
		static const logs::Logger & instance = logs::LoggerFactory::logger("ActionManagerTimer");
		return instance;
	}

	/*!
	 * \brief Liste des actions à executer.
	 */
	utils::PointerList<IAction*> actions_;

	/*!
	 * \brief Liste des actions à executer en mode timer.
	 */
	utils::PointerList<ITimerListener*> timers_;

	/*!
	 * \brief Vaut \c true si le système doit s'arréter.
	 * \sa ::stop()
	 */
	bool stop_;

	/*!
	 *\brief Chronomètre lié au Minuteur.
	 */
	utils::Chronometer chronoTimer_;

	utils::Mutex mtimer_;
	utils::Mutex maction_;

protected:

	/*!
	 * \brief Execute l'ensemble des actions enregistrées.
	 */
	virtual void execute();

public:

	/*!
	 * \brief Constructeur de la classe.
	 */
	ActionManagerTimer();

	/*!
	 * \brief Destructeur de la classe.
	 */
	inline virtual ~ActionManagerTimer()
	{
	}

	/*!
	 * \brief Retourne le nombre d'actions.
	 */
	inline int countActions()
	{
		maction_.lock();
		int size = this->actions_.size();
		maction_.unlock();
		return size;
	}

	/*!
	 * \brief Retourne le nombre d'actions.
	 */
	inline int countTimers()
	{
		mtimer_.lock();
		int size = this->timers_.size();
		mtimer_.unlock();
		return size;
	}

	/*!
	 * \brief Ajout d'une action.
	 * \param action
	 *        L'action à ajouter.
	 */
	inline void addAction(IAction * action)
	{
		maction_.lock();
		actions_.push_back(action);
		maction_.unlock();
	}

	/*!
	 * \brief Ajout d'une action en timer.
	 * \param action
	 *        L'action à ajouter.
	 */
	inline void addTimer(ITimerListener * timer)
	{
		if (timer->timeSpan() != 0)
		{
			mtimer_.lock();
			timers_.push_back(timer);
			mtimer_.unlock();
		}
	}

	inline void stopTimer(std::string name)
	{
		mtimer_.lock();
		bool found = false;
		utils::PointerList<ITimerListener *>::iterator save;
		utils::PointerList<ITimerListener *>::iterator i = timers_.begin();
		while (i != timers_.end())
		{
			ITimerListener * timer = *i;
			if (timer->info() == name)
			{
				save = i;
				found = true;
				timer->onTimerEnd(chronoTimer_);
			}
			i++;
		}
		if (found)
			timers_.erase(save);
		else
			logger().error() << "Timer " << name << " not found !!" << logs::end;

		mtimer_.unlock();
	}

	/*!
	 * \brief Vide la liste des actions actuellement enregistrées.
	 */
	inline void clearActions()
	{
		maction_.lock();
		actions_.clear();
		maction_.unlock();
	}

	/*!
	 * \brief L'appel à cette méthode signale au thread qu'il doit s'arrêter
	 * (proprement).
	 *
	 * L'utilisation de la méthode ActionManager::stop() permet de
	 * savoir si le thread associé est arrêté.
	 */
	inline void stop()
	{
		this->stop_ = true;
	}

	/*!
	 * \brief Affiche via le logger les différentes actions en cours.
	 */
	void debugActions();
};


#endif