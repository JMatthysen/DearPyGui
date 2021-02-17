#pragma once

#include <string>
#include <vector>
#include <map>
#include "mvCore.h"
#include "mvPython.h"

namespace Marvel {

	struct mvDrawCmdConfig
	{
		std::string drawing;
		std::string tag;
	};

	struct mvModifyDrawCommandConfig : public mvDrawCmdConfig{};

	struct mvBringDrawCommandForwardConfig : public mvDrawCmdConfig {};

	struct mvBringDrawCommandToFrontConfig : public mvDrawCmdConfig {};

	struct mvSendDrawCommandBackConfig : public mvDrawCmdConfig {};

	struct mvSendDrawCommandToBackConfig : public mvDrawCmdConfig {};

	struct mvGetDrawCommandConfig : public mvDrawCmdConfig {};

	struct mvDeleteDrawCommandConfig : public mvDrawCmdConfig {};

	struct mvDrawImageConfig
	{
		std::string drawing;
		std::string file;
		std::vector<float> pmin;
		std::vector<float> pmax;
		std::vector<float> uv_min{ 0.0, 0.0 };
		std::vector<float> uv_max{ 1.0, 1.0 };
		mvColor color{ 255, 255, 255, 255 };
		std::string tag = "";
	};

	struct mvDrawLineConfig
	{
		std::string drawing;
		std::vector<float> p1;
		std::vector<float> p2;
		mvColor color;
		int thickness;
		std::string tag = "";
	};

	struct mvDrawArrowConfig : public mvDrawLineConfig
	{
		int size;
	};

	struct mvDrawTriangleConfig : public mvDrawLineConfig
	{
		std::vector<float> p3;
		std::vector<float> fill{ 0, 0, 0, -1 };
		float thickness = 1.0;
	};

	struct mvDrawRectangleConfig
	{
		std::string drawing;
		std::vector<float> pmin;
		std::vector<float> pmax;
		mvColor color;
		std::vector<float> fill{ 0, 0, 0, -1 };
		float rounding = 0.0;
		float thickness = 1.0;
		std::string tag = "";
	};

	struct mvDrawQuadConfig : public mvDrawLineConfig
	{
		std::vector<float> p3;
		std::vector<float> p4;
		std::vector<float> fill{ 0, 0, 0, -1 };
		float thickness = 1.0;
	};

	struct mvDrawTextConfig
	{
		std::string drawing;
		std::vector<float> pos;
		std::string text;
		mvColor color{ 0,0,0,-1 };
		int size = 10;
		std::string tag = "";
	};

	struct mvDrawCircleConfig
	{
		std::string drawing;
		std::vector<float> center;
		float radius;
		mvColor color;
		int segments = 0;
		float thickness = 1.0;
		std::vector<float> fill{ 0, 0, 0, -1 };
		std::string tag = "";
	};

	struct mvDrawPolylineConfig
	{
		std::string drawing;
		std::vector<std::vector<float>> points;
		mvColor color;
		bool closed = false;
		float thickness = 1.0;
		std::string tag = "";
	};

	struct mvDrawPolygonConfig
	{
		std::string drawing;
		std::vector<std::vector<float>> points;
		mvColor color;
		std::vector<float> fill{ 0,0,0,-1 };
		float thickness = 1.0;
		std::string tag = "";
	};

	struct mvDrawBezierCurveConfig
	{
		std::string drawing;
		std::vector<float> p1;
		std::vector<float> p2;
		std::vector<float> p3;
		std::vector<float> p4;
		mvColor color;
		float thickness = 1.0;
		int segments = 0;
		std::string tag = "";
	};

	struct mvClearDrawingConfig
	{
		std::string draw;
	};

	class mvDrawCmd;

	PyObject* modify_draw_command        (PyObject* self, PyObject* args, PyObject* kwargs);
	PyObject* get_draw_command           (PyObject* self, PyObject* args, PyObject* kwargs);
	PyObject* bring_draw_command_forward (PyObject* self, PyObject* args, PyObject* kwargs);
	PyObject* bring_draw_command_to_front(PyObject* self, PyObject* args, PyObject* kwargs);
	PyObject* send_draw_command_back     (PyObject* self, PyObject* args, PyObject* kwargs);
	PyObject* send_draw_command_to_back  (PyObject* self, PyObject* args, PyObject* kwargs);
	PyObject* delete_draw_command        (PyObject* self, PyObject* args, PyObject* kwargs);
	PyObject* clear_drawing              (PyObject* self, PyObject* args, PyObject* kwargs);

	class mvDrawList
	{

	public:

		static void InsertParser(std::map<std::string, mvPythonParser>* parsers);

	public:

		~mvDrawList();

		void             draw         (ImDrawList* drawlist, float x, float y);
		void             clear        ();
		void             addCommand   (mvRef<mvDrawCmd> command);
		void             deleteCommand(const std::string& tag);
		void             bringForward (const std::string& tag);
		void             bringToFront (const std::string& tag);
		void             sendBack     (const std::string& tag);
		void             sendToBack   (const std::string& tag);
		mvRef<mvDrawCmd> getCommand   (const std::string& tag);

	private:

		std::vector<mvRef<mvDrawCmd>> m_commands;

	};

}