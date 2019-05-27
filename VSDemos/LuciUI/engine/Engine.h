class Engine
{
public:
	Engine();
	~Engine();

	void Run(std::list<IRenderable*>);
};