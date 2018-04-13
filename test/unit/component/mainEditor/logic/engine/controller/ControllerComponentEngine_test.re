open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

let _ =
  describe(
    "engine:controller component",
    () => {
      let sandbox = getSandboxDefaultVal();
      beforeEach(
        () => {
          TestTool.closeContractCheck();
          sandbox := createSandbox();
          MainEditorSceneTool.initStateAndGl(sandbox);
          MainEditorSceneTool.createDefaultScene(
            sandbox,
            MainEditorSceneTool.setFirstBoxTobeCurrentGameObject
          )
        }
      );
      afterEach(
        () => {
          restoreSandbox(refJsObjToSandbox(sandbox^));
          TestTool.openContractCheck()
        }
      );
      describe(
        "test add component",
        () =>
          describe(
            "test add sourceInstance component",
            () => {
              test(
                "engineStateForEdit and engineStateForRun shouldn't have sourceInstance before add it",
                () =>
                  (
                    StateLogicService.getEditEngineState()
                    |> GameObjectComponentEngineService.hasSourceInstanceComponent(
                         MainEditorSceneTool.unsafeGetCurrentGameObject()
                       ),
                    StateLogicService.getRunEngineState()
                    |> GameObjectComponentEngineService.hasSourceInstanceComponent(
                         MainEditorSceneTool.unsafeGetCurrentGameObject()
                       )
                  )
                  |> expect == (false, false)
              );
              test(
                "current gameObject should have sourceInstance component after add it",
                () => {
                  let component =
                    BuildComponentTool.buildInspectorComponent(
                      TestTool.buildEmptyAppState(),
                      InspectorTool.buildFakeAllShowComponentConfig()
                    );
                  BaseEventTool.triggerComponentEvent(
                    component,
                    OperateComponentEventTool.triggerClickAddComponentEvent
                  );
                  BaseEventTool.triggerComponentEvent(
                    component,
                    OperateComponentEventTool.triggerClickAddSourceInstanceEvent
                  );
                  (
                    StateLogicService.getEditEngineState()
                    |> GameObjectComponentEngineService.hasSourceInstanceComponent(
                         DiffComponentTool.getEditEngineComponent(
                           DiffType.GameObject,
                           MainEditorSceneTool.unsafeGetCurrentGameObject()
                         )
                       ),
                    StateLogicService.getRunEngineState()
                    |> GameObjectComponentEngineService.hasSourceInstanceComponent(
                         MainEditorSceneTool.unsafeGetCurrentGameObject()
                       )
                  )
                  |> expect == (true, true)
                }
              )
            }
          )
      )
    }
  );