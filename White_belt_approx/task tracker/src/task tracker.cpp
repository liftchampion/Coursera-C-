#include <vector>
#include <iostream>
#include <map>
#include <tuple>
using namespace std;

/*enum class TaskStatus {
	NEW,
	IN_PROGRESS,
	TESTING,
	DONE
};

using TasksInfo = map<TaskStatus, int>;*/

class TeamTasks {
public:

	TasksInfo GetPersonTasksInfo(const string& person) const {
		TasksInfo person_tasks;
		person_tasks[TaskStatus::NEW] = team.at(person)[0];
		person_tasks[TaskStatus::IN_PROGRESS] = team.at(person)[1];
		person_tasks[TaskStatus::TESTING] = team.at(person)[2];
		person_tasks[TaskStatus::DONE] = team.at(person)[3];
		return person_tasks;
	}
	void AddNewTask(const string& person) {
		if (team.count(person) == 0) {
			vector<int> new_tasks(4);
			team[person] = new_tasks;
		}
		team[person][0]++;
	}
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {
		TasksInfo refreshed;
		TasksInfo not_refreshed;
		vector<int> new_tasks(4, 0);

		if (team.count(person) == 0) {
			return tie(refreshed, not_refreshed);
		}

		for (int i = 0; i < 3; i++) {
			if (task_count > team[person][i]) {
				new_tasks[i] -= team[person][i];
				task_count -= team[person][i];
				new_tasks[i + 1] += team[person][i];
				refreshed[static_cast<TaskStatus>(i + 1)] = team[person][i];
			}
			else {
				new_tasks[i] -= task_count;
				new_tasks[i + 1] += task_count;
				refreshed[static_cast<TaskStatus>(i + 1)] = task_count;
				not_refreshed[static_cast<TaskStatus>(i)] = team[person][i] - task_count;
				task_count = 0;
			}
		}
		for (int i = 0; i < 4; i++) {
			team[person][i] += new_tasks[i];
		}
		return tie(refreshed, not_refreshed);
	}

private:
	map<string, vector<int>> team;
};


/*
void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Ilia");
  for (int i = 0; i < 3; ++i) {
    tasks.AddNewTask("Ivan");
  }
  cout << "Ilia's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
  cout << "Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  cout << "***Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Ivan", 2);
  cout << "Updated Ivan's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Ivan's tasks: ";
  PrintTasksInfo(untouched_tasks);

  cout << "***Ivan's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

  return 0;
}*/
