let hasSourceInstanceComponent = (gameObject) =>
  GameObjectComponentEngineService.hasSourceInstanceComponent(gameObject) |> StateLogicService.getEngineState;