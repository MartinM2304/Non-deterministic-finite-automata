cmake_minimum_required(VERSION 3.24)
project(NDFA04)

set(CMAKE_CXX_STANDARD 17)

add_executable(NDFA04 main.cpp "data structures/MyVector.hpp" "data structures/MySet.hpp" NDFA/Automata.cpp NDFA/Automata.h NDFA/Transition.hpp NDFA/State.cpp NDFA/State.h Commands/Command.h "data structures/String.cpp" "data structures/String.h" "data structures/MyQueue.hpp" Commands/BuildAutomata.h Commands/CommandFactory.cpp Commands/CommandFactory.h Commands/BuildaAutomata.cpp Commands/LoadFromFile.cpp Commands/LoadFromFile.h Commands/BuildUnion.cpp Commands/BuildUnion.h Commands/ConcatAutomats.cpp Commands/ConcatAutomats.h Commands/KleeneStarAutomat.cpp Commands/KleeneStarAutomat.h Commands/InteresctionBuild.cpp Commands/InteresctionBuild.h Commands/ComplementBuild.cpp Commands/ComplementBuild.h Commands/DifferenceBuild.cpp Commands/DifferenceBuild.h)
