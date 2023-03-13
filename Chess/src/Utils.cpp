#include "Utils.h"
#include <iostream>

namespace Utils {
	std::vector<std::string> splitString(std::string string, std::string delimiter) {
		std::vector<std::string> fields;
		Utils::trim(string);

		size_t pos = 0;
		std::string token;

		while ((pos = string.find(delimiter)) != std::string::npos) {
			token = string.substr(0, pos);
			fields.push_back(token);
			string.erase(0, pos + delimiter.length());
		}
		fields.push_back(string);
		return fields;
	}

	// trim function credits: https://stackoverflow.com/a/217605

	// trim from start (in place)
	inline void trimStart(std::string& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
			return !std::isspace(ch);
			}));
	}

	// trim from end (in place)
	inline void trimEnd(std::string& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
			return !std::isspace(ch);
			}).base(), s.end());
	}

	// trim from both ends (in place)
	inline void trim(std::string& s) {
		trimStart(s);
		trimEnd(s);
	}

	namespace Debug {
		void printVector(std::vector<std::string> vec, bool asList) {
			std::cout << "vec size: " << vec.size() << std::endl;
			if (asList) {
				for (size_t i{0}; i < vec.size(); ++i)
					std::cout << "vec[" << i << "]: " << vec.at(i) << std::endl;
			}
			else {
				for (auto& item : vec)
					std::cout << item << ' ';
				std::cout << std::endl;
			}
		}

		void printBoard(const BoardEngine& board) {
			auto& pieces = board.getRawBoard();
			for (int8_t i{ 0 }; i < 8; ++i) {
				for (int8_t j{ 0 }; j < 8; ++j) {
					Piece piece = pieces[i * 8 + j];

					char pieceStr;
					switch (piece.type) {
						case Piece::Type::King:
							pieceStr = 'k';
							break;
						case Piece::Type::Queen:
							pieceStr = 'q';
							break;
						case Piece::Type::Bishop:
							pieceStr = 'b';
							break;
						case Piece::Type::Knight:
							pieceStr = 'n';
							break;
						case Piece::Type::Rook:
							pieceStr = 'r';
							break;
						case Piece::Type::Pawn:
							pieceStr = 'p';
							break;
						default:
							pieceStr = '_';
							break;
					}
					if (pieces[i * 8 + j].color == Piece::Color::White) pieceStr = toupper(pieceStr);
					std::cout << pieceStr << ' ';
				}
				std::cout << std::endl;
			}
			std::cout << "En Passant Pawn: " << (int)board.getEnPassantPawn() << std::endl;
			std::cout << "White Castling Rights (King Side/Queen Side): " << board.getCastlingRights(Piece::Color::White).at(0) << '/' << board.getCastlingRights(Piece::Color::White).at(1) << std::endl;
			std::cout << "Black Castling Rights (King Side/Queen Side): " << board.getCastlingRights(Piece::Color::Black).at(0) << '/' << board.getCastlingRights(Piece::Color::Black).at(1) << std::endl;
		}

		void print(std::string msg, bool endLine) {
			std::cout << msg;
			if (endLine) std::cout << std::endl;
		}
	}
}